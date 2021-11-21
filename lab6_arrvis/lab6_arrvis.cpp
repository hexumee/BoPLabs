#include "framework.h"
#include "lab6_arrvis.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
int a[10];
int n;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6ARRVIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6ARRVIS));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6ARRVIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB6ARRVIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   FILE *f;
   fopen_s(&f, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab6_arrvis\\text.txt", "rt");
   fscanf_s(f, "%d", &n);

   for (int i = 0; i < n; i++)
       fscanf_s(f, "%d", &a[i]);

   fclose(f);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int maxOfArray() {
    int max = a[0];

    for (int i = 0; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

void DrawLine(HDC hdc, int x0, int y0, int x, int y) {
    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x, y);
}

void DrawPlot(HDC hdc, int x, int y) {
    int moa = maxOfArray();
    DrawLine(hdc, x, y, x, y-30*moa/2);
    DrawLine(hdc, x, y, x+60*n/2, y);
    POINT ptx[3] = { {x, y-30*moa/2-10}, {x-10, y-30*moa/2}, {x+10, y-30*moa/2}};
    POINT pty[3] = { {x+60*n/2+10, y}, {x+60*n/2, y-10}, {x+60*n/2, y+10}};
    Polygon(hdc, ptx, 3);
    Polygon(hdc, pty, 3);
}

void DrawSector(HDC hdc, int x0, int y0, int x, int y, bool color, bool different) {
    if (color)
        if (different) {
            HBRUSH brush = CreateSolidBrush(RGB(72, 196, 196));
            SelectObject(hdc, brush);
            Rectangle(hdc, x0, y0, x, y);
            DeleteObject(brush);
        } else {
            HBRUSH brush = CreateSolidBrush(RGB(196, 196, 196));
            SelectObject(hdc, brush);
            Rectangle(hdc, x0, y0, x, y);
            DeleteObject(brush);
        }
    else {
        HBRUSH obrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, obrush);
        Rectangle(hdc, x0, y0, x, y);
        DeleteObject(obrush);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            {
                int wmId = LOWORD(wParam);

                switch (wmId) {
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

                int plot_center_x = 200;
                int plot_center_y = 400;
                DrawPlot(hdc, plot_center_x, plot_center_y);
                for (int i = 0; i < n; i++) {
                    DrawSector(hdc, plot_center_x+i*20, plot_center_y-(a[i]*10), plot_center_x+(i+1)*20, plot_center_y, false, false);
                }
            
                plot_center_x = 800;
                plot_center_y = 400;
                DrawPlot(hdc, plot_center_x, plot_center_y);

                int min = a[0], max = a[0], maxidx = 0, minidx = 0, m = 0;
                for (int i = 0; i < n; i++) {
                    if (a[i] > max) {
                        max = a[i];
                        maxidx = i;
                    }
                    if (a[i] < min) {
                        min = a[i];
                        minidx = i;
                    }
                }

                if (maxidx > minidx) {
                    int c = minidx+1;
                    while (c != n-1) {
                        if (a[c] % 2 != 0) {
                            a[c-m] = a[c];
                        } else {
                            m++;
                        }
                        c++;
                        if (c == maxidx) {
                            a[c-m] = a[c];
                            break;
                        }
                    }
                    for (int i = maxidx+1; i < n; i++) {
                        a[i-m] = a[i];
                    }
                } else {
                    int c = maxidx+1;
                    while (c != n-1) {
                        if (a[c] % 2 != 0) {
                            a[c-m] = a[c];
                        } else {
                            m++;
                        }
                        c++;
                        if (c == minidx) {
                            a[c-m] = a[c];
                            break;
                        }
                    }
                    for (int i = minidx+1; i < n; i++) {
                        a[i-m] = a[i];
                    }
                }

                max = a[0], min = a[0];
                for (int i = 0; i < n-m; i++) {
                    if (a[i] > max) {
                        max = a[i];
                        maxidx = i;
                    }
                    if (a[i] < min) {
                        min = a[i];
                        minidx = i;
                    }
                }

                for (int i = 0; i < n-m; i++) {
                    if (i == maxidx || i == minidx) {
                        DrawSector(hdc, plot_center_x+i*20, plot_center_y-(a[i]*10), plot_center_x+(i+1)*20, plot_center_y, true, false);
                    } else {
                        DrawSector(hdc, plot_center_x+i*20, plot_center_y-(a[i]*10), plot_center_x+(i+1)*20, plot_center_y, false, false);
                    }
                }

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
