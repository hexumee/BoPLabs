#include "framework.h"
#include "lab9_2darray.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
int arr[10][10];
int are[10][10];
int w = 0, h = 0;
int minx = 0, miny = 0, minv = 0;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB92DARRAY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB92DARRAY));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB92DARRAY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB92DARRAY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    FILE *f;
    fopen_s(&f, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab9_2darray\\text.txt", "rt");
    fscanf_s(f, "%d%d", &h, &w);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fscanf_s(f, "%d", &arr[i][j]);
            are[i][j] = arr[i][j];
        }
    }

    minv = arr[0][0];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (arr[i][j] < minv) {
                minv = arr[i][j];
                minx = j;
                miny = i;
            }
        }
    }

    for (int i = miny+1; i < h; i++) {
        for (int j = 0; j < w; j++) {
            are[i-1][j] = arr[i][j];
        }
    }
                        
    for (int i = 0; i < h; i++) {
        for (int j = minx+1; j < w; j++) {
            are[i][j-1] = are[i][j];
        }
    }

    fclose(f);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
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

                HBRUSH b1 = CreateSolidBrush(RGB(255, 0, 127));
                HBRUSH b2 = CreateSolidBrush(RGB(0, 127, 255));
                HBRUSH b3 = CreateSolidBrush(RGB(127, 255, 0));
                HBRUSH b4 = CreateSolidBrush(RGB(127, 127, 0));

                for (int i = 0; i < h; i++) {
                    for (int j = 0; j < w; j++) {
                        switch (arr[i][j]) {
                            case 1:
                                SelectObject(hdc, b1);
                                break;
                            case 2:
                                SelectObject(hdc, b2);
                                break;
                            case 3:
                                SelectObject(hdc, b3);
                                break;
                            case 4:
                                SelectObject(hdc, b4);
                        }
                        Rectangle(hdc, 100+20*j, 100+20*i, 120+20*j, 120+20*i);
                    }
                }

                for (int i = 0; i < h-1; i++) {
                    for (int j = 0; j < w-1; j++) {
                        switch (are[i][j]) {
                            case 1:
                                SelectObject(hdc, b1);
                                break;
                            case 2:
                                SelectObject(hdc, b2);
                                break;
                            case 3:
                                SelectObject(hdc, b3);
                                break;
                            case 4:
                                SelectObject(hdc, b4);
                        }
                        Rectangle(hdc, 240+20*j, 100+20*i, 260+20*j, 120+20*i);
                    }
                }

                DeleteObject(b1);
                DeleteObject(b2);
                DeleteObject(b3);
                DeleteObject(b4);

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
