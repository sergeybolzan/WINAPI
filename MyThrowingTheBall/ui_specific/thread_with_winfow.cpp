#include "stdafx.h"
#include "thread_with_winfow.h"
#include "all_messages.h"
#include "DrawingDialog.h"
#include <interlockedapi.h>


namespace ttb_thread
{

    BOOL CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // window procedure

    void UIThreadFunction(SThreadInitialData* const a_pInitialData)
    {
        if (!a_pInitialData)
            return;

        // it's drawing thread
        // so do higher fps
        auto t_Handle = ::GetCurrentThread();
        ::SetThreadPriority(t_Handle, ABOVE_NORMAL_PRIORITY_CLASS);

        CMessageQueue& t_toUIThread = a_pInitialData->m_toUIThread;

        try
        {
            do
            {
                // init controls
                // need to execute this  for normal working with windows
                INITCOMMONCONTROLSEX iCCE;
                iCCE.dwSize = sizeof(iCCE);
                iCCE.dwICC = ICC_WIN95_CLASSES;
                if (!::InitCommonControlsEx(&iCCE))
                {
                   throw std::exception("UI thread failed to initialize system for windows creation");
                }

                DrawingDialog wnd(a_pInitialData);//начинается логика по созданию окна

                ::CreateDialogParam(
                    ::GetModuleHandle(NULL),
                    MAKEINTRESOURCE(wnd.id), 0,
                    (DLGPROC)WndProc,
                    (LPARAM)&wnd);


                  MSG msg;

                  while ( wnd.m_hWnd && ::GetMessage(&msg, NULL, 0, 0))
                  {

                     if ( !::IsDialogMessage(wnd.m_hWnd, &msg))
                     {
                        ::TranslateMessage(&msg);
                        ::DispatchMessage(&msg);
                     };
                  };
                  WLOGFILE("Exit by user request.");
                  break;

            }while(true);
        }catch(std::exception ex)
        {
            WLOGFILE(ex.what());
        }
    }


// just forward everything into our class
BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   DrawingDialog* const pD = (DrawingDialog*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

   switch ( message )
   {
      case WM_INITDIALOG:
      {
         ::SetWindowLongPtr(hWnd, GWL_USERDATA, lParam); // our function should be here to process messages
         DrawingDialog* const pD = (DrawingDialog*)lParam;
         pD->m_hWnd = hWnd;
         return pD->OnInitDialog();
      }

      case WM_CLOSE:
         if ( pD )
            pD->OnClose();
         return TRUE;

      case WM_COMMAND:

         if ( pD )
            return pD->OnCommand(wParam,lParam);

         return TRUE;

      default:
         return pD ? pD->OnMessage(message, wParam, lParam) : FALSE;
   };
}


};


