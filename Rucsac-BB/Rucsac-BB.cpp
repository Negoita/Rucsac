// Rucsac-BB.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include "Rucsac-BB.h"

#define MAX_LOADSTRING 100

// Global Variables:
							// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND greutateMaxima;
HWND greutatea, valoarea, numele, butonDeAdaugare, butonDeStart;
HWND lista;
HWND butonStergere;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	v = (obiect*)malloc(100 * sizeof(obiect));
	h = (obiect*)malloc(100 * sizeof(obiect));
	nrObiecte = 0;


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RUCSACBB, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RUCSACBB));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RUCSACBB));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RUCSACBB);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 550, 400, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId) 
		{
		case BN_CLICKED:
			if ((HWND)lParam == butonDeAdaugare)
			{
				WCHAR buff1[100];
				WCHAR buff2[100];
				WCHAR buff3[100];
				WCHAR buff[1000];
				int numar;
				GetWindowText(valoarea, buff1, 100);
				GetWindowText(greutatea, buff2, 100);
				GetWindowText(numele, buff3, 100);
				if (wcsnlen_s(buff1, 100) == 0 || wcsnlen_s(buff2, 100) == 0 || wcsnlen_s(buff3, 100) == 0)
				{
					MessageBox(hWnd, L"Introduceti Valoarile!", L"ERROR", MB_ICONERROR);
				}
				else 
				{
					wcscpy_s(buff, 1000, buff3); 
					wcscat_s(buff, 1000, L": V- ");
					wcscat_s(buff, 1000, buff1);
					wcscat_s(buff, 1000, L"; G- ");
					wcscat_s(buff, 1000, buff2);
					wcscat_s(buff, 1000, L";");
					SendMessage(lista, LB_ADDSTRING, NULL, (LPARAM)buff);

					obiect obj;
					numar = _wtoi(buff1);
					obj.valoare = numar;
					numar = _wtoi(buff2);
					obj.greutate = numar;
					obj.id = nrObiecte;
					wcscpy_s(obj.nume, 20, buff3);
					h[nrObiecte] = obj;
					/*v[nrObiecte] = obj;*/
					nrObiecte++;
				}
			}
			if ((HWND)lParam == butonDeStart)
			{
				WCHAR buff[100];
				GetWindowText(greutateMaxima, buff, 100);
				if (wcsnlen_s(buff, 100) == 0)
				{
					MessageBox(hWnd, L"Introduceti Greutatea MAX!", L"ERROR", MB_ICONERROR);
					break;
				}
				capacitate = _wtoi(buff);
				for (int i = 0; i < nrObiecte; i++)
				{
					v[i] = h[i];
				}
				solve(v, h, nrObiecte, capacitate);
			} 
			if ((HWND)lParam == butonStergere)
			{
				int ancora = SendMessage(lista, LB_GETANCHORINDEX, NULL, NULL);
				SendMessage(lista, LB_DELETESTRING, ancora, NULL);

				nrObiecte--;
				obiect aux;

				aux = h[ancora];
				h[ancora] = h[nrObiecte];
				h[nrObiecte] = aux;

				/*aux = v[ancora];
				v[ancora] = v[nrObiecte];
				v[nrObiecte] = aux;*/
			}

			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TextOut(hdc, 20, 22, L"Greutate MAX:", 14);

		TextOut(hdc, 20, 102, L"Valoarea:", 10);
		TextOut(hdc, 20, 132, L"Greutatea:", 11);
		TextOut(hdc, 20, 162, L"Numele:", 8);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		greutateMaxima = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER,
			120, 20, 40, 20, hWnd, NULL, hInst, NULL);
		
		valoarea = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER,
			120, 100, 40, 20, hWnd, NULL, hInst, NULL);
		greutatea = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER,
			120, 130, 40, 20, hWnd, NULL, hInst, NULL);
		numele = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			120, 160, 85, 20, hWnd, NULL, hInst, NULL);
		butonDeAdaugare = CreateWindow(L"BUTTON", L"Adauga", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_BORDER,
			210, 100, 100, 80, hWnd, NULL, hInst, NULL);
		butonDeStart = CreateWindow(L"BUTTON", L"Alege", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_BORDER,
			210, 20, 100, 80, hWnd, NULL, hInst, NULL);
		lista = CreateWindow(L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
			320, 20, 210, 300, hWnd, NULL, hInst, NULL);
		butonStergere = CreateWindow(L"BUTTON", L"Sterge", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_BORDER,
			120, 200, 100, 80, hWnd, NULL, hInst, NULL);
	}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
