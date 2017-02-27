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
		// присоединяемся к окну
		void Attach(const HWND ahwnd, DrawingDialog* apParent);
		void Detach(void); // освобождаем окно

		// координаты внутри нашей кнопки
		void OnMouseMove(int x, int y);
	protected:
		HWND m_hWnd = nullptr;// идентификатор окна
		DrawingDialog* m_pParent = nullptr; // указатель на диалог-папу

		// процедура обработки сообщений
		// окна - старая
		WNDPROC m_oldWndProc = nullptr; // old messages processor for this window

	};

};