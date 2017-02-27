#ifndef DRAW_FIELD325987FLDKJWHFE
#define DRAW_FIELD325987FLDKJWHFE

// class for draw SD_VECTOR's data as a 2 dimensional curve
//
// for choose 2 axises from SD_VECTOR use AxisSelector



#include "DrawBuffer.h"

class DrawingDialog; // data holder

namespace ttb_thread
{

class AxisSelector;


    class DrawField
    {
    public:
       DrawField(void);
       /*virtual */ ~DrawField(void);

       virtual void OnDestroy(void);
       void Attach(const HWND ahwnd, DrawingDialog* apParent, std::shared_ptr<AxisSelector>& a_Axises);
       void Detach(void);
       /*virtual */ LPARAM OnMessage(UINT message, WPARAM wParam, LPARAM lParam);

       void ExecuteCycleDraw(); // now we draw in dynamic whole flight
       HWND m_hWnd;
    protected:
       WNDPROC m_oldWndProc; // old messages processor for this window
       std::shared_ptr<AxisSelector> m_Axises; // here we decide wich axises we use


    protected: // drawing specific members and procedures
        DrawBuffer m_image; // here draw in a buffer, then bitblt into control
        void PaintLayout(WPARAM wParam, LPARAM lParam); // WM_PAINT
        HDC m_dc; // our window DC
        GdiObject m_oldImage; // our old image from DC
        DrawingDialog* m_dataHolder;

        void PaintBackground(const HDC ahdc, const RECT& arc);
        void PaintAxis(const HDC ahdc, const RECT& arc); // draw axis lines

        void PaintTrace(const HDC ahdc, const RECT& arc);// paint trace, final position and emulate motion


        // dynamic motion of the ball
        double m_FlightTime; // full flight time
        double m_FlightMoment; // we search for this fly moment to draw dynamic
        FILETIME m_StartMotion; // when we start cycling
        bool m_bDrawDynamicDone; // false before any cycle, true when draw done
        void PaintDynamic(const HDC ahdc, const POINT& arc, double a_time); // dynamical ball painting
        void CalculateFlightMoment();// for reset m_bDrawDynamicDone && calculate m_FlightMoment - dynamic painting logic
    protected:
        // 
         GdiObject m_brushAxis;
         GdiObject m_penAxis;

         GdiObject m_brushRed;
         GdiObject m_brushBlue;
         GdiObject m_penRed;
         GdiObject m_penBlue;

    };
};


#endif