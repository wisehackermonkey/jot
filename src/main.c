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

    // Set the background color to #444654
    SetClassLongPtr(g_hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(68, 70, 84)));

    // Set the font to monospaced system font
    HFONT hFont = CreateFont(
        14,                      // Height of font
        0,                       // Width of font
        0,                       // Angle of escapement
        0,                       // Orientation angle
        FW_NORMAL,               // Font weight
        FALSE,                   // Italic
        FALSE,                   // Underline
        FALSE,                   // Strikeout
        ANSI_CHARSET,            // Character set identifier
        OUT_DEFAULT_PRECIS,      // Output precision
        CLIP_DEFAULT_PRECIS,     // Clipping precision
        DEFAULT_QUALITY,         // Output quality
        FF_DONTCARE | FIXED_PITCH, // Family and pitch
        TEXT("Consolas")         // Font name (monospaced system font)
    );

    SendMessage(g_hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

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
