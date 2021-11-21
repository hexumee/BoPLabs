#include "framework.h"
#include "lab4_stars.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4STARS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4STARS));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4STARS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4STARS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void DrawStar(HDC hdc, int x, int y, int size) {
    POINT star[8] = { {x, y-size}, {x+size/4, y-size/4}, {x+size, y}, {x+size/4, y+size/4}, {x, y+size}, {x-size/4, y+size/4}, {x-size, y}, {x-size/4, y-size/4} };
    Polygon(hdc, star, 8);
}

void DrawStarF(HDC hdc, int x, int y, int size) {
    POINT star[10] = { {x, y-size}, {x+size/4, y-size/4}, {x+size, y-size/4}, {x+size/2.5, y+size/4}, {x+size/1.5, y+size}, {x, y+size/2}, {x-size/1.5, y+size}, {x-size/2.5, y+size/4}, {x-size, y-size/4}, {x-size/4, y-size/4} };
    Polygon(hdc, star, 10);
}

void RecuStar(HDC hdc, int x, int y, int size, int depth) {
    if (depth <= 0) return;
    DrawStar(hdc, x, y, size);
    RecuStar(hdc, x-size, y, size/2, depth-1); // левый верх
    RecuStar(hdc, x, y+size, size/2, depth-1); // правый низ
    RecuStar(hdc, x, y-size, size/2, depth-1); // левый низ
    RecuStar(hdc, x+size, y, size/2, depth-1); // правый верх
}

void RecuStarF(HDC hdc, int x, int y, int size, int depth) {
    if (depth <= 0) return;
    DrawStarF(hdc, x, y, size);
    RecuStarF(hdc, x-size, y-size/4, size/2, depth-1); // лево
    RecuStarF(hdc, x+size, y-size/4, size/2, depth-1); // право
    RecuStarF(hdc, x, y-size, size/2, depth-1); // верх
    RecuStarF(hdc, x-size/1.5, y+size, size/2, depth-1); // левый низ
    RecuStarF(hdc, x+size/1.5, y+size, size/2, depth-1); // правый низ
}

void RecuStarFoF(HDC hdc, int x, int y, int size, int depth) {
    if (depth <= 0) return;
    DrawStar(hdc, x, y, size);
    RecuStarF(hdc, x-size, y, size/2, depth-1); // левый верх
    RecuStarF(hdc, x, y+size, size/2, depth-1); // правый низ
    RecuStarF(hdc, x, y-size, size/2, depth-1); // левый низ
    RecuStarF(hdc, x+size, y, size/2, depth-1); // правый верх
}

void RecuStarCo(HDC hdc, int x, int y, int size, int depth) {
    if (depth <= 0) return;
    DrawStarF(hdc, x, y, size);
    RecuStarFoF(hdc, x-size, y-size/4, size/2, depth-1); // лево
    RecuStarFoF(hdc, x+size, y-size/4, size/2, depth-1); // право
    RecuStarFoF(hdc, x, y-size, size/2, depth-1); // верх
    RecuStarFoF(hdc, x-size/1.5, y+size, size/2, depth-1); // левый низ
    RecuStarFoF(hdc, x+size/1.5, y+size, size/2, depth-1); // правый низ
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);

                switch (wmId) {
                    case IDM_ABOUT:
                        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        break;
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                RecuStar(hdc, 200, 200, 50, 3);
                RecuStarF(hdc, 500, 200, 50, 3);
                RecuStarCo(hdc, 800, 200, 50, 3);

                EndPaint(hWnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }

    return (INT_PTR)FALSE;
}
