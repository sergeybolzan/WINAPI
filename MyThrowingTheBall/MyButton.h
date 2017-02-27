#pragma once
class DrawingDialog;

namespace ttb_thread
{

	class MyButton
	{
	public:
		MyButton();
		~MyButton();

		friend LPARAM CALLBACK ProcMyButton(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		// �������������� � ����
		void Attach(const HWND ahwnd, DrawingDialog* apParent);
		void Detach(void); // ����������� ����

		// ���������� ������ ����� ������
		void OnMouseMove(int x, int y);
	protected:
		HWND m_hWnd = nullptr;// ������������� ����
		DrawingDialog* m_pParent = nullptr; // ��������� �� ������-����

		// ��������� ��������� ���������
		// ���� - ������
		WNDPROC m_oldWndProc = nullptr; // old messages processor for this window

	};

};