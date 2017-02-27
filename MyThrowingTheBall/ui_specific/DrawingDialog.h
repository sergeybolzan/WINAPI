#ifndef FLKEGLKWETH123907LFKJGHMAINWIN
#define FLKEGLKWETH123907LFKJGHMAINWIN

// dialog for presenting UI
// we create this dialog, set own message procedure for it, and working inside.

#include "resource.h"
#include "thread_with_winfow.h"
#include "drawfield.h"
#include "MyButton.h"


class DrawingDialog
{
   DrawingDialog();
public:
   DrawingDialog(ttb_thread::SThreadInitialData* const a_pInitialData);
   ~DrawingDialog(void);
   enum
   {
      id = IDD_DIALOD_FOR_DRAW,
   };

   BOOL OnInitDialog(void);
   BOOL OnCommand(WPARAM wParam, LPARAM lParam); // WM_COMMAND income

   void OnClose(void);// for whole application

   BOOL OnTimer(const int aTimerID); // timer for redraw
   void OnUpdateNecessary(void); // here actual invalidate for windows executed

   BOOL OnMessage(UINT message, WPARAM wParam, LPARAM lParam); // messages for this window

public:
   HWND m_hWnd; // should be established from outside after creating of the dialog

protected:

    friend class ttb_thread::DrawField; // lets access m_positions and min&max directly

    std::map<double, SD_VECTOR> m_positions; // time positions
    SD_VECTOR m_minimumPos; // minimum pos on track
    SD_VECTOR m_maximumPos; // maximum pos on track

	ttb_thread::MyButton m_button; // моя кнопка

    ttb_thread::DrawField m_fieldXZ; // drawing x & z plane
    ttb_thread::DrawField m_fieldYZ; // drawing y & z plane

    ttb_thread::SThreadInitialData* const m_pInitialData; // no need to delete - it's pointer to the main thread data - commands linkage object

    uint32_t m_timer_ID; // our timer for invalidate
};



#endif


