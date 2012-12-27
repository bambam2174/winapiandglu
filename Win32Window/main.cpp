#define WIN32_LEAN_AND_MEAN
#define IDC_MAIN_BUTTON 201
#pragma comment(linker, "/subsystem:windows")

#include <Windows.h>
#include "Person.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX windowClass;
	HWND hwnd;
	MSG msg;
	bool done;

	Person *ich;
	ich = new Person();

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&windowClass)) {
		return 0;
	}

	hwnd = CreateWindowEx(NULL,
						"MyClass", 
						ich->vorname,
						WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
						100, 100,
						400, 400,
						NULL,
						NULL,
						hInstance,
						NULL);
	
	if (!hwnd)
		return 0;
	done = false;

	while(!done) 
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		
		if (msg.message == WM_QUIT) {
			done = true;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	//OutputDebugString((LPCSTR)hwnd);
	PAINTSTRUCT paintStruct;

	static HDC hDC;
	static HGLRC hRC;
	HWND hWndButton;
	char string[] = "Hello World!";

	switch(message) {
		case WM_CREATE:
			hWndButton=CreateWindowEx(NULL, 
									"BUTTON",
									"OK",
									WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
									50,
									220,
									100,
									24,
									hwnd,
									(HMENU)IDC_MAIN_BUTTON,
									GetModuleHandle(NULL),
									NULL);
			hDC = GetDC(hwnd);
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			break;
		case WM_DESTROY:
			wglMakeCurrent(hDC, NULL);
			wglDeleteContext(hRC);
			PostQuitMessage(0);
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			hDC = BeginPaint(hwnd, &paintStruct);
			SetTextColor(hDC, COLORREF(0x00ff0000));
			TextOut(hDC, 150, 150, string, sizeof(string)-1);
			EndPaint(hwnd, &paintStruct);
			return 0;
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_MAIN_BUTTON:
					MessageBox(hwnd, "Button OK wurde geklickt", "ClickEvent", NULL);
					break;
				default:
					break;
			}
		default:
			break;
	}
	return (DefWindowProc(hwnd, message, wParam, lParam));
}