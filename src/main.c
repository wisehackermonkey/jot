#include <stdio.h>
#include <windows.h>

// Global variables
HWND g_hWnd;
HWND g_hEdit;

// Function to create the main window
BOOL CreateMainWindow(HINSTANCE hInstance, int nCmdShow) {
    // Create the main window
    g_hWnd = CreateWindow(
        TEXT("EDIT"),      // Edit control class
        TEXT(""),          // No initial text
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,     // X position
        CW_USEDEFAULT,     // Y position
        500,               // Width
        600,               // Height
        NULL,              // Parent window
        NULL,              // Menu
        hInstance,         // Instance handle
        NULL               // No additional parameters
    );

    if (!g_hWnd) {
        return FALSE;
    }

    // Create the edit control
    g_hEdit = g_hWnd;

    ShowWindow(g_hWnd, nCmdShow);
    UpdateWindow(g_hWnd);

    return TRUE;
}

// Main entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!CreateMainWindow(hInstance, nCmdShow)) {
        return 1;
    }

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
