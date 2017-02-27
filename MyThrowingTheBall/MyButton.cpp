#include "stdafx.h"
#include "MyButton.h"
#include "DrawingDialog.h"


namespace ttb_thread
{

	LPARAM CALLBACK ProcMyButton(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		MyButton* const pC = (MyButton*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

		switch (message)
		{
		case WM_MOUSEMOVE:
			pC->OnMouseMove(0, 0);
			return TRUE;
		case WM_DESTROY:
			if (pC)
			{
				pC->Detach();
			}
			return TRUE;
		default:
			return ::CallWindowProc(pC->m_oldWndProc, pC->m_hWnd, message, wParam, lParam);
		};
	}


	MyButton::MyButton()
	{
	}


	MyButton::~MyButton()
	{
	}


	// присоединяемся к окну
	void MyButton::Attach(const HWND ahwnd, DrawingDialog* apParent)
	{
		m_pParent = apParent; // установили указатель на диалог отца
		m_hWnd = ahwnd; // сохранили идентификатор окна (хэндл)

		// для окна сказали что наш указатель это пользовательские данные
		::SetWindowLongPtr(m_hWnd, GWL_USERDATA, LPARAM(this));

		// установили обработчик процедуры окна
		m_oldWndProc = (WNDPROC)::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(&ProcMyButton));

	}
	void MyButton::Detach(void)
	{
		::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(m_oldWndProc));
		m_oldWndProc = NULL;
		::SetWindowLongPtr(m_hWnd, GWL_USERDATA, 0); // set our pointer
		m_hWnd = NULL;
	}

	// координаты внутри нашей кнопки
	void MyButton::OnMouseMove(int x, int y)
	{
		std::cout << "asdasdasd";
	}
};
