#include "stdafx.h"
#include "Headers.h"
#include "Road.h"
#include "UFO.h"
#include "CrossRoad.h"
#include "Car.h"
#include "Vector.h"
#include <iostream>
#include  <time.h>

/*
сделать чтобы  машины не возвращали


Вектор - это хранилище
Когда мы строим хранилище 
что нам надо знать?
НАДО ЗНАТЬ ЧТО(ТИП) мы будем хранить
*/

Vector<DrawObject*> drawObjects;
Vector<Road*> roads; //список всех дорог

bool finish = false;
UFO* Ufo;


clock_t tstart;
void CreateObjectsForDraw(){
	MessageBox(NULL, L"Up arrow - go up\nDown arrow - go down\nRight arrow - go right\nLeft arrow- go left\nYour task: destroy all cars", L"Controls", MB_OK);
	tstart = clock();
	CrossRoad*  crossRoad1 = new CrossRoad(10, 10);
	CrossRoad*  crossRoad2 = new CrossRoad(10, 450);
	CrossRoad*  crossRoad3 = new CrossRoad(10, 900);
	CrossRoad*  crossRoad4 = new CrossRoad(200, 450);
	CrossRoad*  crossRoad5 = new CrossRoad(300, 10);
	CrossRoad*  crossRoad6 = new CrossRoad(300, 350);
	CrossRoad*  crossRoad7 = new CrossRoad(200, 900);
	CrossRoad*  crossRoad8 = new CrossRoad(350, 350);
	CrossRoad*  crossRoad9 = new CrossRoad(600, 10);
	CrossRoad*  crossRoad10 = new CrossRoad(475, 350);
	CrossRoad*  crossRoad11 = new CrossRoad(600, 350);
	CrossRoad*  crossRoad12 = new CrossRoad(475, 625);
	CrossRoad*  crossRoad13 = new CrossRoad(475, 900);
	CrossRoad*  crossRoad14 = new CrossRoad(750, 900);
	CrossRoad*  crossRoad15 = new CrossRoad(750, 625);
	CrossRoad*  crossRoad16 = new CrossRoad(750, 350);
	CrossRoad*  crossRoad17 = new CrossRoad(750, 180);
	CrossRoad*  crossRoad18 = new CrossRoad(750, 10);
	CrossRoad*  crossRoad19 = new CrossRoad(950, 10);
	CrossRoad*  crossRoad20 = new CrossRoad(950, 180);
	CrossRoad*  crossRoad21 = new CrossRoad(950, 350);
	CrossRoad*  crossRoad22 = new CrossRoad(1200, 10);
	CrossRoad*  crossRoad23 = new CrossRoad(1200, 180);
	CrossRoad*  crossRoad24 = new CrossRoad(1200, 350);
	CrossRoad*  crossRoad25 = new CrossRoad(1200, 900);
	Road *road1 = new  Road(crossRoad1, crossRoad5);
	Road *road2 = new  Road(crossRoad1, crossRoad2);
	Road *road3 = new  Road(crossRoad2, crossRoad3);
	Road *road4 = new  Road(crossRoad2, crossRoad4);
	Road *road5 = new  Road(crossRoad3, crossRoad7);
	Road *road6 = new  Road(crossRoad7, crossRoad4);
	Road *road7 = new  Road(crossRoad5, crossRoad6);
	Road *road8 = new  Road(crossRoad5, crossRoad9);
	Road *road9 = new  Road(crossRoad8, crossRoad10);
	Road *road10 = new  Road(crossRoad10, crossRoad12);
	Road *road11 = new  Road(crossRoad12, crossRoad13);
	Road *road12= new  Road(crossRoad7, crossRoad13);
	Road *road13 = new  Road(crossRoad10, crossRoad11);
	Road *road14 = new  Road(crossRoad9, crossRoad11);
	Road *road15 = new  Road(crossRoad11, crossRoad16);
	Road *road16 = new  Road(crossRoad12, crossRoad15);
	Road *road17 = new  Road(crossRoad13, crossRoad14);
	Road *road18 = new  Road(crossRoad16, crossRoad15);
	Road *road19 = new  Road(crossRoad15, crossRoad14);
	Road *road20 = new  Road(crossRoad9, crossRoad18);
	Road *road21 = new  Road(crossRoad18, crossRoad19);
	Road *road22 = new  Road(crossRoad17, crossRoad20);
	Road *road23 = new  Road(crossRoad16, crossRoad21);
	Road *road24 = new  Road(crossRoad19, crossRoad20);
	Road *road25 = new  Road(crossRoad20, crossRoad21);
	Road *road26 = new  Road(crossRoad21, crossRoad24);
	Road *road27 = new  Road(crossRoad20, crossRoad23);
	Road *road28 = new  Road(crossRoad19, crossRoad22);
	Road *road29 = new  Road(crossRoad22, crossRoad23);
	Road *road30 = new  Road(crossRoad23, crossRoad24);
	Road *road31 = new  Road(crossRoad25, crossRoad24);
	Road *road32 = new  Road(crossRoad25, crossRoad14);
	Road *road33 = new  Road(crossRoad12, crossRoad16);
	Road *road34 = new  Road(crossRoad18, crossRoad17);
	Road *road35 = new  Road(crossRoad17, crossRoad16);

	Ufo = new UFO(20,20);

	drawObjects.push_back(crossRoad1);
	drawObjects.push_back(crossRoad2);
	drawObjects.push_back(crossRoad3);
	drawObjects.push_back(crossRoad4);
	drawObjects.push_back(crossRoad5);
	drawObjects.push_back(crossRoad6);
	drawObjects.push_back(crossRoad7);
	drawObjects.push_back(crossRoad8);
	drawObjects.push_back(crossRoad9);
	drawObjects.push_back(crossRoad10);
	drawObjects.push_back(crossRoad11);
	drawObjects.push_back(crossRoad12);
	drawObjects.push_back(crossRoad13);
	drawObjects.push_back(crossRoad14);
	drawObjects.push_back(crossRoad15);
	drawObjects.push_back(crossRoad16);
	drawObjects.push_back(crossRoad17);
	drawObjects.push_back(crossRoad18);
	drawObjects.push_back(crossRoad19);
	drawObjects.push_back(crossRoad20);
	drawObjects.push_back(crossRoad21);
	drawObjects.push_back(crossRoad22);
	drawObjects.push_back(crossRoad23);
	drawObjects.push_back(crossRoad24);
	drawObjects.push_back(crossRoad25);
	drawObjects.push_back(road1);
	drawObjects.push_back(road2);
	drawObjects.push_back(road3);
	drawObjects.push_back(road4);
	drawObjects.push_back(road5);
	drawObjects.push_back(road6);
	drawObjects.push_back(road7);
	drawObjects.push_back(road8);
	drawObjects.push_back(road9);
	drawObjects.push_back(road10);
	drawObjects.push_back(road11);
	drawObjects.push_back(road12);
	drawObjects.push_back(road13);
	drawObjects.push_back(road14);
	drawObjects.push_back(road15);
	drawObjects.push_back(road16);
	drawObjects.push_back(road17);
	drawObjects.push_back(road18);
	drawObjects.push_back(road19);
	drawObjects.push_back(road20);
	drawObjects.push_back(road21);
	drawObjects.push_back(road22);
	drawObjects.push_back(road23);
	drawObjects.push_back(road24);
	drawObjects.push_back(road25);
	drawObjects.push_back(road26);
	drawObjects.push_back(road27);
	drawObjects.push_back(road28);
	drawObjects.push_back(road29);
	drawObjects.push_back(road30);
	drawObjects.push_back(road31);
	drawObjects.push_back(road32);
	drawObjects.push_back(road33);
	drawObjects.push_back(road34);
	drawObjects.push_back(road35);

	roads.push_back(road1);
	roads.push_back(road2);
	roads.push_back(road3);
	roads.push_back(road4);
	roads.push_back(road5);
	roads.push_back(road6);
	roads.push_back(road7);
	roads.push_back(road8);
	roads.push_back(road9);
	roads.push_back(road10);
	roads.push_back(road11);
	roads.push_back(road12);
	roads.push_back(road13);
	roads.push_back(road14);
	roads.push_back(road15);
	roads.push_back(road16);
	roads.push_back(road17);
	roads.push_back(road18);
	roads.push_back(road19);
	roads.push_back(road20);
	roads.push_back(road21);
	roads.push_back(road22);
	roads.push_back(road23);
	roads.push_back(road24);
	roads.push_back(road25);
	roads.push_back(road26);
	roads.push_back(road27);
	roads.push_back(road28);
	roads.push_back(road29);
	roads.push_back(road30);
	roads.push_back(road31);
	roads.push_back(road32);
	roads.push_back(road33);
	roads.push_back(road34);
	roads.push_back(road35);

	for (int i = 0; i < 70; i++){
		Road *randomRoad = roads[rand() % roads.getSize()];
		Car *newCar = new Car(randomRoad, Color::Red);
		drawObjects.push_back(newCar);
	}
	drawObjects.push_back(Ufo);

}

VOID OnPaint(HDC hdc) //каждые 300 милисекунд
{
	RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
	RedrawWindow(GetDesktopWindow(), &rect, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	Graphics graphics(hdc);
	graphics.Clear(Color(255, 0, 0, 0));
	
	for (int i = 0; i < drawObjects.getSize(); i++)
		drawObjects[i]->draw(graphics);

	for (int i = 0; i < roads.getSize(); i++)
		roads[i]->go();

	
	//у каждой дороги перебрать все машины
	//посмореть совпадает ли машина  и НЛО
	//удалить машину из дороги

	//надо перебрать все дороги
	int count = 0;
	int ufo_x = Ufo->getX();
	int ufo_y = Ufo->getY();
	for (int i = 0; i < roads.getSize(); i++){
		for (int j = 0; j < roads[i]->getAllCars()->getSize(); j++){
			count++;
			int car_x = (*roads[i]->getAllCars())[j]->getX();
			int car_y = (*roads[i]->getAllCars())[j]->getY();
			int dx = abs(ufo_x - car_x);
			int dy = abs(ufo_y - car_y);
			int d = sqrt(dx*dx + dy*dy);
			if (d <= 40){
				drawObjects.remove((*roads[i]->getAllCars())[j]);
				roads[i]->getAllCars()->remove((*roads[i]->getAllCars())[j]);
			}
		}
	}

	if (count == 0 && finish==false){
		finish = true;
		int a = (clock() - tstart) / 1000;
		wchar_t buffer[256];
		wsprintfW(buffer, L"%d", a);
		wcscat(buffer, L" s. ");
		MessageBox(NULL, buffer, L"YOU WIN!", MB_OK);
	}
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{

	srand(time(NULL));
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	CreateObjectsForDraw();
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	SetTimer(hWnd, 0, 100, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;
	HDC          hdcMem;
	HBITMAP      hbmMem;
	HANDLE       hOld;

	switch (message)
	{
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, 1500, 1200);
		hOld = SelectObject(hdcMem, hbmMem);
		OnPaint(hdcMem);
		BitBlt(hdc, 0, 0, 1500, 1200, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
	{
		InvalidateRect(hWnd, NULL, NULL);
		break;
	}
	

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
				Ufo->setX(Ufo->getX() - 10);
			break;
		case VK_RIGHT:
			Ufo->setX(Ufo->getX() + 10);
			break;
		case VK_UP:
			Ufo->setY(Ufo->getY() - 10);
			break;
		case VK_DOWN:
			Ufo->setY(Ufo->getY() + 10);
			break;
		}


	https://msdn.microsoft.com/en-us/library/windows/desktop/ms646268(v=vs.85).aspx


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc




// http://ideone.com/bBJJRx