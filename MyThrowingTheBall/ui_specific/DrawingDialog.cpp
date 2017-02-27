#include "stdafx.h"

#include <iomanip>
#include "DrawingDialog.h"
#include "thread_with_winfow.h"
#include "all_messages.h"
#include "constants.h"
#include "AxisSelector.h"

#undef max

using namespace ttb_thread;

DrawingDialog::DrawingDialog()
    :m_hWnd(NULL)
    , m_pInitialData(nullptr)
    , m_timer_ID(d_timerDrawUpdate)
{
}

DrawingDialog::DrawingDialog(SThreadInitialData* const a_pInitialData)
   :m_hWnd(NULL)
   , m_pInitialData(a_pInitialData)
   , m_timer_ID(d_timerDrawUpdate)
{
    m_minimumPos.x_axis = m_minimumPos.y_axis = m_minimumPos.z_axis = std::numeric_limits<double>::max();
    m_maximumPos.x_axis = m_maximumPos.y_axis = m_maximumPos.z_axis = std::numeric_limits<double>::lowest();
}

DrawingDialog::~DrawingDialog(void)
{
}

BOOL DrawingDialog::OnInitDialog(void)
{
   m_fieldXZ.Attach(::GetDlgItem(m_hWnd, IDC_X_Z_PLANE), this, std::shared_ptr<AxisSelector>(new XZ_AxisSelector));
   m_fieldYZ.Attach(::GetDlgItem(m_hWnd, IDC_Y_Z_PLANE), this, std::shared_ptr<AxisSelector>(new YZ_AxisSelector));

   m_button.Attach(::GetDlgItem(m_hWnd, IDCANCEL), this); // присоединяем кнопку

    ::ShowWindow(m_hWnd, SW_SHOW);
    ::UpdateWindow(m_hWnd);
    ::SetForegroundWindow(m_hWnd);

   m_timer_ID = ::SetTimer(m_hWnd, m_timer_ID, d_time__Update, NULL);
   if (m_timer_ID == NULL)
   {
       throw std::exception("failed to update fly animation");
   }

   return TRUE; // first in tab stop order
   // return FALSE if you are set keyboard focus
}


BOOL DrawingDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
   const int low = LOWORD(wParam);

   switch( low )
   {
   case IDCANCEL:
      OnClose();
      break;
   };
   return FALSE;
}




void DrawingDialog::OnClose(void)
{
   ::KillTimer(m_hWnd, m_timer_ID);
   ::DestroyWindow(m_hWnd);
   ::PostQuitMessage(0);
}

BOOL DrawingDialog::OnMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch ( message )
   {
   case WM_TIMER:
      return OnTimer((int)wParam);
   }
   return FALSE;
}

void DrawingDialog::OnUpdateNecessary()
{
    // redraw curves and set text for coordinates
    ::InvalidateRect(m_fieldXZ.m_hWnd, NULL, FALSE);
    ::InvalidateRect(m_fieldYZ.m_hWnd, NULL, FALSE);
    if (m_positions.size() > 0)
    {
        SD_VECTOR t_vec =  m_positions.rbegin()->second;

        std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > t_ss;
        t_ss << std::setprecision(7) << XSDV(t_vec); 

        ::SendMessage(::GetDlgItem(m_hWnd, IDC_XVALUE), WM_SETTEXT, 0, (LPARAM)t_ss.str().c_str());
        t_ss.str(TEXT(""));
        t_ss << YSDV(t_vec); 
        ::SendMessage(::GetDlgItem(m_hWnd, IDC_YVALUE), WM_SETTEXT, 0, (LPARAM)t_ss.str().c_str());
    }


}

BOOL DrawingDialog::OnTimer(const int aTimerID)
{
    if (m_timer_ID == aTimerID)
    {

        CMessageQueue::T_MessageSequence t_sequence;
        m_pInitialData->m_toUIThread.NextMessages(t_sequence);

        while (!t_sequence.empty())
        {
            auto t_msg = t_sequence.front();
            t_sequence.pop();

            if (EMESSAGE_TYPE::message_no_more_data ==  t_msg->Type())
            {
                WLOGFILE("UI thread meets quit request. Means - No more data.");
                m_fieldXZ.ExecuteCycleDraw();
                m_fieldYZ.ExecuteCycleDraw();
            }

            if (EMESSAGE_TYPE::message_data ==  t_msg->Type())
            {
                WLOGFILE("data income");
                CMessageTimeEvent* const t_datamessage = reinterpret_cast<CMessageTimeEvent*>(t_msg.get());
                SD_VECTOR&& t_vec = t_datamessage->Position();

                m_positions[t_datamessage->When()] = t_vec; // actually we can throw here after memory realloc - well in the case we any way need to terminate


                // check/save min
                // +-.1 - for 1 point of incoming data
                if (XSDV(t_vec) < XSDV(m_minimumPos))
                    XSDV(m_minimumPos) = XSDV(t_vec) - 0.1;
                if (YSDV(t_vec) < YSDV(m_minimumPos))
                    YSDV(m_minimumPos) = YSDV(t_vec) - 0.1;
                if (ZSDV(t_vec) < ZSDV(m_minimumPos))
                    ZSDV(m_minimumPos) = ZSDV(t_vec) - 0.1;

                // check/save max
                if (XSDV(t_vec) > XSDV(m_maximumPos))
                    XSDV(m_maximumPos) = XSDV(t_vec) + 0.1;
                if (YSDV(t_vec) > YSDV(m_maximumPos))
                    YSDV(m_maximumPos) = YSDV(t_vec) + 0.1;
                if (ZSDV(t_vec) > ZSDV(m_maximumPos))
                    ZSDV(m_maximumPos) = ZSDV(t_vec) + 0.1;
            }

        }
        OnUpdateNecessary(); // dynamic drawing
    }
   return FALSE;
}



