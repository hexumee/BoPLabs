#include "framework.h"
#include "lab10_maze.h"
#include <stdio.h>
#include <string>

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
char maze[30][30];
int maze_w, maze_h;
int px0, py0, px1, py1;
int pxl, pyl, fxl, fyl;
int clev = 1, levs = 2;
HDC hdc;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                LoadFile();
void                RenderLevel();
void                CheckForPortal(HWND);
bool                CheckForCollide();
void                InitMaze();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB10MAZE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB10MAZE));
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB10MAZE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB10MAZE);
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

   LoadFile();
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
                hdc = BeginPaint(hWnd, &ps);
                RenderLevel();
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case VK_LEFT:
                    px0 -= 20;
                    py0 -= 20;
                    pxl--;
                    break;
                case VK_RIGHT:
                    px0 += 20;
                    py0 += 20;
                    pxl++;
                    break;
                case VK_UP:
                    py1 -= 20;
                    px1 -= 20;
                    pyl--;
                    break;
                case VK_DOWN:
                    py1 += 20;
                    px1 += 20;
                    pyl++;
                    break;  
            }
            InvalidateRect(hWnd, NULL, true);
            CheckForPortal(hWnd);
            if (CheckForCollide()) {
                MessageBoxA(hWnd, "Проиграл", "Сообщение", NULL);
                clev = 1;
                LoadFile();
                RenderLevel();
            }
            InvalidateRect(hWnd, NULL, true);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void RenderLevel() {
    HBRUSH wallBrush = CreateSolidBrush(RGB(160, 55, 35));
    HBRUSH playerBrush = CreateSolidBrush(RGB(235, 235, 0));
    HBRUSH finBrush = CreateSolidBrush(RGB(105, 105, 255));

    for (int i = 0; i < maze_h; i++) {
        for (int j = 0; j < maze_w; j++) {
            if (maze[i][j] == *"X") {
                SelectObject(hdc, wallBrush);
                Rectangle(hdc, 100+20*j, 100+20*i, 120+20*j, 120+20*i);
            } else if (maze[i][j] == *"@") {
                SelectObject(hdc, finBrush);
                Rectangle(hdc, 103+20*j, 103+20*i, 117+20*j, 117+20*i);
            } else if (maze[i][j] == *"#") {
                SelectObject(hdc, playerBrush);
                Rectangle(hdc, px0, px1, py0, py1);
            }
        }
    }

    DeleteObject(wallBrush);
    DeleteObject(playerBrush);
    DeleteObject(finBrush);
}

void LoadFile() {
    FILE* f;
    char *a = (char*)malloc(sizeof(char)*(strlen("C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab10_maze\\lev")+1+4+1));
    char this_level[] = {clev+'0', '\0'};
    strcpy(a, "C:\\Users\\hexumee\\Desktop\\osnprog_labs\\lab10_maze\\lev");
    strcat(a, this_level);
    strcat(a, ".txt");
    fopen_s(&f, a, "rt");
    fscanf_s(f, "%d%d", &maze_w, &maze_h);

    int cr = 0;
    while (cr != maze_h) {
        int cc = 0;
        while(cc != maze_w) {
            char s;
            fscanf_s(f, "%c", &s);
            if (s != '\n') {
                maze[cr][cc] = s;
                if (s == *"#") {
                    px0 = 125+20*(cc-1);
                    px1 = 125+20*(cr-1);
                    py0 = 135+20*(cc-1);
                    py1 = 135+20*(cr-1);
                    pxl = cc;
                    pyl = cr;
                } else if (s == *"@") {
                    fxl = cc;
                    fyl = cr;
                }
                cc++;
            }
        }
        cr++;
    }
    fclose(f);
    free(a);
}

void CheckForPortal(HWND hWnd) {
    if (pxl == fxl) {
        if (pyl == fyl) {
            clev++;
            if (clev >= levs+1) {
                MessageBoxA(hWnd, "Конец игры", "Сообщение", NULL);
                DestroyWindow(hWnd);
            } else {
                LoadFile();
                RenderLevel();
            }
        }
    }
}

bool CheckForCollide() {
    for (int i = 0; i < maze_h; i++) {
        for (int j = 0; j < maze_w; j++) {
            if (maze[i][j] == *"X") {
                if (pxl == j && pyl == i) {
                    return true;
                }
            }
        }
    }
    return false;
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
