#include "stdafx.h"
#include "drawfield.h"
#include "DrawingDialog.h"
#include "AxisSelector.h"


// the int  a  located between a1 and a2
// let's found ax (return)
// ax located between a3 and a4 like a between a1 and a2
//
// need operaions
//  - + * /
//////////////////////////////////////////////
//  a1 - a2    a3 - a4                      //
//  ~~~~~~~ == ~~~~~~~                      //
//  a  - a2    ax - a4                      //
//////////////////////////////////////////////
template <typename T, typename T2, typename T3>
T2 Proportional(T const a1, T const a2, T2 a3, T2 a4, T3 const a)
{
   return (T2)((a4 - a3) * (a - a2) / (a2 - a1) + a4);
}

#define AXISPOS 7 // pixels



namespace ttb_thread
{
    LPARAM CALLBACK ControlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
       DrawField* const pC = (DrawField*)GetWindowLongPtr(hWnd, GWL_USERDATA);

       switch ( message )
       {
       case WM_DESTROY:
          if ( pC )
             pC->OnDestroy();
          return TRUE;
       default:
          return pC->OnMessage(message, wParam, lParam);
       };
    }

    DrawField::DrawField(void)
       :m_hWnd(NULL)
       , m_oldWndProc(NULL)
       , m_dataHolder(nullptr)
       , m_bDrawDynamicDone(false)
    {
        m_StartMotion.dwHighDateTime = 0;
        m_StartMotion.dwLowDateTime = 0;

        COLORREF traceColor = RGB(240, 40, 18);
        COLORREF itemColor = RGB(17, 44, 242);
        COLORREF axisColor = RGB(200, 240, 180);

        m_brushRed.Attach(::CreateSolidBrush(traceColor));
        m_brushBlue.Attach(::CreateSolidBrush(itemColor));
        m_brushAxis.Attach(::CreateSolidBrush(axisColor));
        m_penRed.Attach(::CreatePen(PS_SOLID, 0, traceColor));
        m_penBlue.Attach(::CreatePen(PS_SOLID, 0, itemColor));
        m_penAxis.Attach(::CreatePen(PS_SOLID, 0, axisColor));
    }

    DrawField::~DrawField(void)
    {
    }

    void DrawField::OnDestroy(void)
    {
       Detach();
    }


    LPARAM DrawField::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
           case WM_NCPAINT:
              {
                 return TRUE; // nothing to do as far as we will draw whole rect within WM_PAINT
              };
           case WM_PAINT:
              {
                 PaintLayout(wParam, lParam);
                 return TRUE;
              }
        default:
            break;
        }
        return ::CallWindowProc(m_oldWndProc, m_hWnd, message, wParam, lParam);
    }

    void DrawField::Attach(const HWND ahwnd, DrawingDialog* apParent, std::shared_ptr<AxisSelector>& a_Axises)
    {
        m_hWnd = ahwnd;
        m_Axises = a_Axises;
        m_dataHolder = apParent;

        ::SetWindowLongPtr(m_hWnd, GWL_USERDATA, LPARAM(this)); // set our pointer

        m_oldWndProc = (WNDPROC)::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(&ControlProc));

    }

void DrawField::Detach(void)
{
   ::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(m_oldWndProc));
   m_oldWndProc = NULL;
   ::SetWindowLongPtr(m_hWnd, GWL_USERDATA, 0); // set our pointer
   m_hWnd = NULL;
}


void DrawField::PaintBackground(const HDC ahdc, const RECT& arc)
{
    const HBRUSH brush = ::CreateSolidBrush(0);
    ::FillRect(ahdc, &arc, brush);
    ::DeleteObject(brush);
}

void DrawField::PaintAxis(const HDC ahdc, const RECT& arc)
{
   // adjust DC
   GdiObject oldpen(::SelectObject(ahdc, m_penAxis));
   GdiObject oldbrush(::SelectObject(ahdc, m_brushAxis));

    POINT t_drawAt = {AXISPOS, AXISPOS};
    ::MoveToEx(ahdc, t_drawAt.x, t_drawAt.y, NULL);
    t_drawAt.y += arc.bottom - arc.top - 2 * AXISPOS;
    ::LineTo(ahdc, t_drawAt.x, t_drawAt.y);
    t_drawAt.x += arc.right - arc.left - 2 * AXISPOS;
    ::LineTo(ahdc, t_drawAt.x, t_drawAt.y);

   ::SelectObject(ahdc, oldpen.Detach());
   ::SelectObject(ahdc, oldbrush.Detach());

}

void DrawField::PaintTrace(const HDC ahdc, const RECT& arc)
{
    if (m_dataHolder == nullptr)
        return;
    if (m_dataHolder->m_positions.size() < 1)
        return;

    CalculateFlightMoment(); // dynamic drawing here reset

   // adjust DC
   GdiObject oldpen(::SelectObject(ahdc, m_penRed));
   GdiObject oldbrush(::SelectObject(ahdc, m_brushRed));
   do 
   { // drawing inside - using local synonims of variables
        RECT toDrawIn = arc; // we draw inside this rect

        // axis should not be crossed
        toDrawIn.left += AXISPOS;
        toDrawIn.bottom -= AXISPOS;

        std::map<double, SD_VECTOR>& t_map = m_dataHolder->m_positions; // synonim

        SD_VECTOR& t_minimum = m_dataHolder->m_minimumPos; // synonim
        SD_VECTOR& t_maximum = m_dataHolder->m_maximumPos; // synonim
        auto it = t_map.begin();
        double t_when = it->first;
        SD_VECTOR& t_where = it->second; // synonim

        // actual pos should be mapped into this rect toDrawIn
        POINT pnt;
        pnt.x = Proportional(m_Axises->Horizontal(t_minimum), m_Axises->Horizontal(t_maximum), toDrawIn.left, toDrawIn.right, m_Axises->Horizontal(t_where));

        // bottom and top sequence in next call: as far as actual y goes from top to bottom
        pnt.y = Proportional(m_Axises->Vertical(t_minimum), m_Axises->Vertical(t_maximum), toDrawIn.bottom, toDrawIn.top, m_Axises->Vertical(t_where));

        ::MoveToEx(ahdc, pnt.x, pnt.y, NULL); // set pointer to line from

        const auto t_sz = (double)t_map.size();


        // we need to restrict count of drawing points
        //  lets limit it with:
        auto t_MaxLines = toDrawIn.right - toDrawIn.left + toDrawIn.bottom - toDrawIn.top;
        double t_Step = (const double)t_sz / (double)t_MaxLines;
        if (t_Step < 1.)
            t_Step = 1.;
        decltype(t_MaxLines) t_Pos = 0; // position where we inside vector right now
        decltype(t_MaxLines) t_NextPosToDraw = t_Pos; // we will draw next line only if t_Pos matches
        double t_CurrentDrawStep =  t_Step; // line to the next lining step at once, as far as we are at the beginning with MoveTo
        t_NextPosToDraw = (LONG) floor(t_CurrentDrawStep + 0.5);
        for (it = t_map.begin(); it != t_map.end(); ++it)
        {
            SD_VECTOR& t_where = it->second;

            const POINT pnt = {
                Proportional(m_Axises->Horizontal(t_minimum), m_Axises->Horizontal(t_maximum), toDrawIn.left, toDrawIn.right, m_Axises->Horizontal(t_where)),
                Proportional(m_Axises->Vertical(t_minimum), m_Axises->Vertical(t_maximum), toDrawIn.bottom, toDrawIn.top, m_Axises->Vertical(t_where))
            };
            PaintDynamic(ahdc, pnt, it->first);
            if (t_NextPosToDraw == t_Pos || t_Pos == t_sz)
            {
                ::LineTo(ahdc, pnt.x, pnt.y);
                t_CurrentDrawStep += t_Step; // line to the next lining step at once, as far as we are at the beginning with MoveTo
                t_NextPosToDraw = (LONG) floor(t_CurrentDrawStep + 0.5);
            }
            ++t_Pos; // to the next position
            if (t_Pos == t_sz)
            {
                Ellipse(ahdc, pnt.x - AXISPOS, pnt.y + AXISPOS, pnt.x + AXISPOS, pnt.y - AXISPOS);
             }
        }

   }while (false);
   ::SelectObject(ahdc, oldpen.Detach());
   ::SelectObject(ahdc, oldbrush.Detach());
}




void DrawField::PaintLayout(WPARAM wParam, LPARAM lParam) // WM_PAINT
{
   RECT rc;
   {
      if ( 0 == ::GetUpdateRect(m_hWnd, &rc, FALSE) )
         return;
   }
   PAINTSTRUCT ps;
   HDC hdc = ::BeginPaint(m_hWnd, &ps);

   m_image.Init(hdc, rc); // ensure - image of enough size
   // Paint into m_image as DC // operator *

   // start with painting background
   PaintBackground(*m_image, rc);

   PaintAxis(*m_image, rc);

   PaintTrace(*m_image, rc);

   // copy result image to control
   ::BitBlt(hdc, rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      *m_image, rc.left, rc.top, SRCCOPY);

   ::EndPaint(m_hWnd, &ps); 

}

void DrawField::CalculateFlightMoment()
{
    m_bDrawDynamicDone = false;

    FILETIME t_now;
    ::GetSystemTimeAsFileTime(&t_now);
    int64_t& t_NumTime = *((int64_t*)(&t_now));
    int64_t& t_NumStart = *((int64_t*)(&m_StartMotion));
    // time of cycles simulation
    const double full_Flight = ((double)(t_NumTime) - (double)(t_NumStart)) / 1e7; // need to convert in seconds so divide on 1e7

    m_FlightMoment = full_Flight - floor(full_Flight / m_FlightTime) * m_FlightTime;
}

void DrawField::PaintDynamic(const HDC ahdc, const POINT& pnt, double a_time)
{
    if (m_StartMotion.dwHighDateTime == 0)
        return;

    if (m_bDrawDynamicDone)
        return;
    if (m_FlightMoment > a_time)
        return;
    m_bDrawDynamicDone = true;

    // adjust DC
    GdiObject oldpen(::SelectObject(ahdc, m_penBlue));
    GdiObject oldbrush(::SelectObject(ahdc, m_brushBlue));

    Ellipse(ahdc, pnt.x - AXISPOS, pnt.y + AXISPOS, pnt.x + AXISPOS, pnt.y - AXISPOS);

   ::SelectObject(ahdc, oldpen.Detach());
   ::SelectObject(ahdc, oldbrush.Detach());
}

void DrawField::ExecuteCycleDraw()
{
    ::GetSystemTimeAsFileTime(&m_StartMotion);
    m_FlightTime = m_dataHolder->m_positions.rbegin()->first;
}


};

