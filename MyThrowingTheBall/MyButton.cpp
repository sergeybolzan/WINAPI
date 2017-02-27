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


	// �������������� � ����
	void MyButton::Attach(const HWND ahwnd, DrawingDialog* apParent)
	{
		m_pParent = apParent; // ���������� ��������� �� ������ ����
		m_hWnd = ahwnd; // ��������� ������������� ���� (�����)

		// ��� ���� ������� ��� ��� ��������� ��� ���������������� ������
		::SetWindowLongPtr(m_hWnd, GWL_USERDATA, LPARAM(this));

		// ���������� ���������� ��������� ����
		m_oldWndProc = (WNDPROC)::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(&ProcMyButton));

	}
	void MyButton::Detach(void)
	{
		::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, LPARAM(m_oldWndProc));
		m_oldWndProc = NULL;
		::SetWindowLongPtr(m_hWnd, GWL_USERDATA, 0); // set our pointer
		m_hWnd = NULL;
	}

	// ���������� ������ ����� ������
	void MyButton::OnMouseMove(int x, int y)
	{
		std::cout << "asdasdasd";
	}
};
