#include <windows.h>

// Global variables
HWND g_hWnd;
HWND g_hEdit;
COLORREF g_crBackground = RGB(68, 70, 84); 

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

  switch(msg) {

    case WM_CTLCOLOREDIT:
    {
      HDC hdcEdit = (HDC) wParam;
      SetTextColor(hdcEdit, RGB(255, 255, 255));
      SetBkColor(hdcEdit, g_crBackground); 
      return (INT_PTR)CreateSolidBrush(g_crBackground);
    }

  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Function to create the main window
BOOL CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {

  // Register window class
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW; 
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = NULL;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 
  wc.lpszMenuName = NULL;
  wc.lpszClassName = TEXT("MyWindowClass");
  wc.hIconSm = NULL;
  RegisterClassEx(&wc);

  // Create main window
  g_hWnd = CreateWindow(
      TEXT("MyWindowClass"),
      TEXT("My Window"),
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      500, 600,
      NULL, NULL, hInstance, NULL);

  if (!g_hWnd) {
    return FALSE;
  }

  // Set main window background color
  SetClassLongPtr(g_hWnd, GCLP_HBRBACKGROUND, 
    (LONG_PTR)CreateSolidBrush(RGB(255, 250, 0)));

  // Create font
  HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
    DEFAULT_QUALITY, FF_DONTCARE|FIXED_PITCH, TEXT("Consolas"));

  // Set main window font
  SendMessage(g_hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

  // Register edit control class
  WNDCLASSEX wcEdit;
  wcEdit.cbSize = sizeof(WNDCLASSEX);
  wcEdit.style = CS_HREDRAW | CS_VREDRAW;
  wcEdit.lpfnWndProc = DefWindowProc;
  wcEdit.cbClsExtra = 0;
  wcEdit.cbWndExtra = 0;
  wcEdit.hInstance = hInstance;
  wcEdit.hIcon = NULL;
  wcEdit.hCursor = LoadCursor(NULL, IDC_IBEAM);
  wcEdit.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wcEdit.lpszMenuName = NULL;
  wcEdit.lpszClassName = TEXT("EditControl");
  wcEdit.hIconSm = NULL;
  RegisterClassEx(&wcEdit);


// Create edit control
g_hEdit = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    TEXT("EDIT"), 
    NULL,
    WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
    0, 0, 500, 500,
    g_hWnd,
    (HMENU)1, 
    hInstance, 
    NULL);

  ShowWindow(g_hWnd, nCmdShow);
  UpdateWindow(g_hWnd);

  return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
  LPSTR lpCmdLine, int nCmdShow) {
  
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  if(!CreateMainWindow(hInstance, nCmdShow))
    return 1;

  MSG msg;
  while(GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}