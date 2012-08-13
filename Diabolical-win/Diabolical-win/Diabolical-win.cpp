// Diabolical-win.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Diabolical-win.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; 
HWND hWnd;
HDC hDC;
HGLRC hRC;// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);



// Converts VK's to DK's
input::s_DEvent translateKeyEvent(UINT key)
{
	input::s_DEvent result;
	result.type = input::e_keyEvent;
	switch(key)
	{
	case VK_UP:
		result.key = DKeysym::DK_Up;
		break;
	case VK_DOWN:
		result.key = DKeysym::DK_Down;
		break;
	case VK_LEFT:
		result.key = DKeysym::DK_Left;
		break;
	case VK_RIGHT:
		result.key = DKeysym::DK_Right;
		break;
	case 0x43:
		result.key = DKeysym::DK_Key_c;
		break;
	case 0x50:
		result.key = DKeysym::DK_Key_p;
		break;
	case 0x53:
		result.key = DKeysym::DK_Key_s;
		break;
	case 0x31:
		result.key = DKeysym::DK_Key_1;
		break;
	case 0x32:
		result.key = DKeysym::DK_Key_2;
		break;
	case 0x57:
		result.key = DKeysym::DK_Key_w;
		break;
	case 0x54:
		result.key = DKeysym::DK_Key_t;
		break;
	case 0x4D:
		result.key = DKeysym::DK_Key_m;
		break;
	case 0x52:
		result.key = DKeysym::DK_Key_r;
		break;
	case 0x4F:
		result.key = DKeysym::DK_Key_o;
		break;
	case 0x46:
		result.key = DKeysym::DK_Key_f;
		break;
	case 0x47:
		result.key = DKeysym::DK_Key_g;
		break;
	}
	return result;
}

input::s_DEvent translateMouseEvent(WPARAM wParam, LPARAM lParam)
{
  input::s_DEvent result;
  result.type = input::e_mouseEvent;
  switch(wParam)
  {
  case MK_LBUTTON:
    result.mouseEvent.button = input::e_lButton;
    break;
  case MK_RBUTTON:
    result.mouseEvent.button = input::e_rButton;
    break;
  case MK_MBUTTON:
    result.mouseEvent.button = input::e_mButton;
    break;
  default:
    result.mouseEvent.button = input::e_noButton;
    break;
  }
  result.mouseEvent.xPos = GET_X_LPARAM(lParam);
  result.mouseEvent.yPos = GET_Y_LPARAM(lParam);
  return result;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

  if(!application.onInit())
    return -1;

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIABOLICALWIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIABOLICALWIN));

  PeekMessage(&msg,NULL,0,0,PM_NOREMOVE);

	// Main message loop:
	while (msg.message != WM_QUIT && application.isRunning())
	{
    if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
			application.onExecute();
			SwapBuffers(hDC);
    }
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIABOLICALWIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DIABOLICALWIN);
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

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    //  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	 hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,0,0,640,480,NULL,NULL,hInstance,NULL);

   EnableOpenGL(hWnd,&hDC,&hRC);
	 //Renderer::renderer.initRenderer();

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

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
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
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else 
		{
			application.addEvent(translateKeyEvent(wParam));
		}
		break;
  case WM_MOUSEMOVE:
    application.addEvent(translateMouseEvent(wParam,lParam));
    break;
	case WM_DESTROY:
    DisableOpenGL(hWnd,hDC,hRC);
		PostQuitMessage(0);
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

void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	
	// get the device context (DC)
	*hDC = GetDC( hWnd );
	
	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, format, &pfd );
	
	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );
}

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
}