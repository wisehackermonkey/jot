#include <windows.h>

#define ID_TEXTBOX 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"TextEditor";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"JotEditor", L"Jot", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 600, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND hwndTextbox;
    static HBRUSH hBrush;

    switch(msg) {
        case WM_CREATE:
            hwndTextbox = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 
                                        0, 0, 500, 600, hwnd, (HMENU)ID_TEXTBOX, NULL, NULL);
            hBrush = CreateSolidBrush(RGB(0x44, 0x46, 0x54));
            break;
        
        case WM_CTLCOLOREDIT:
            if ((HWND)lp == hwndTextbox) {
                SetBkColor((HDC)wp, RGB(0x44, 0x46, 0x54));
                SetTextColor((HDC)wp, RGB(0xFF, 0xFF, 0xFF)); // setting the text color to white, you can change as you wish
                return (LRESULT)hBrush;
            }
            break;

        case WM_SIZE:
            MoveWindow(hwndTextbox, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
            break;
        
        case WM_DESTROY:
            DeleteObject(hBrush);
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }

    return 0;
}
