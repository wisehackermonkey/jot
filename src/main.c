#include <windows.h>

#define ID_TEXTBOX 1
#define ID_ACCEL_SELECTALL 2
#define ID_ACCEL_CLOSE 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"JotEdit";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowW(L"JotEdit", L"Jot", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 600, NULL, NULL, NULL, NULL);

    ACCEL accel[] = {
        {FCONTROL | FVIRTKEY, 'A', ID_ACCEL_SELECTALL},
        {FCONTROL | FVIRTKEY, 'W', ID_ACCEL_CLOSE},
    };

    HACCEL hAccel = CreateAcceleratorTable(accel, sizeof(accel) / sizeof(ACCEL));

    MSG msg = {0};

    while(GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator(hwnd, hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DestroyAcceleratorTable(hAccel);

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
        
        case WM_COMMAND:
            if (HIWORD(wp) == 1) { // Accelerator command
                switch (LOWORD(wp)) {
                    case ID_ACCEL_SELECTALL:
                        SendMessage(hwndTextbox, EM_SETSEL, 0, -1);
                        break;
                    case ID_ACCEL_CLOSE:
                        SendMessage(hwnd, WM_CLOSE, 0, 0);
                        break;
                }
            }
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
