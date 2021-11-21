#include "framework.h"
#include "lab2_image.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL                DrawLine(HDC, int, int, int, int);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2IMAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2IMAGE));
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2IMAGE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2IMAGE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 816, 639, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void Triangle(HDC hdc, int x, int y, int size) {
    POINT point[3] = { {x, y-size*2}, {x+size*4, y+size}, {x-size*4, y+size}};
    Polygon(hdc, point, 3);
}

void RecuTriangle(HDC hdc, int x, int y, int size, int depth) {
    if (depth <= 0) return;
    Triangle(hdc, x, y, size);
    RecuTriangle(hdc, x, y-size, size/2, depth-1);
    RecuTriangle(hdc, x-size*2, y+size/2, size/2, depth-1);
    RecuTriangle(hdc, x+size*2, y+size/2, size/2, depth-1);
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
                HBRUSH chBrush = CreateSolidBrush(RGB(30, 144, 255));    // голубой
                HPEN chPen = CreatePen(PS_SOLID, 1, RGB(30, 144, 255));
                HBRUSH ghBrush = CreateSolidBrush(RGB(34, 139, 34));     // зеленый
                HPEN ghPen = CreatePen(PS_SOLID, 1, RGB(34, 139, 34));
                HBRUSH ohBrush = CreateSolidBrush(RGB(255, 133, 0));     // оранжевый
                HPEN ohPen = CreatePen(PS_SOLID, 2, RGB(255, 133, 0));
                HBRUSH bhBrush = CreateSolidBrush(RGB(189, 89, 40));     // коричневый
                HBRUSH dbhBrush = CreateSolidBrush(RGB(105, 49, 22));    // темно-коричневый
                HPEN dbhPen = CreatePen(PS_SOLID, 1, RGB(148, 70, 31));  // очтемно-коричневый
                HBRUSH lgrhBrush = CreateSolidBrush(RGB(127, 118, 121)); // ярко-серый
                HBRUSH grhBrush = CreateSolidBrush(RGB(108, 104, 116));  // серый
                HBRUSH dgrhBrush = CreateSolidBrush(RGB(73, 66, 61));    // темно-серый
                HPEN dgrhPen = CreatePen(PS_SOLID, 2, RGB(73, 66, 61));
                HBRUSH whBrush = CreateSolidBrush(RGB(255, 255, 255));   // белый
                HPEN whPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                HBRUSH blhBrush = CreateSolidBrush(RGB(0, 0, 0));        // черный
                HPEN blhPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

                POINT pt[3] = { {460, 330}, {620, 250}, {780, 330} };              // крыша
                POINT pteo[3] = { {234, 395}, {245, 370}, {260, 390} };            // ухо 1
                POINT ptet[3] = { {270, 405}, {295, 380}, {300, 415} };            // ухо 2
                POINT ptt[4] = { {160, 480}, {150, 510}, {125, 530}, {135, 500} }; // хвост
                POINT ptpo[3] = { {150, 570}, {170, 540}, {190, 570} };            // лапа 1
                POINT ptpt[3] = { {260, 570}, {280, 540}, {300, 570} };            // лапа 2


                // #1
                SelectObject(hdc, chBrush);
                SelectObject(hdc, chPen);
                Rectangle(hdc, 0, 0, 800, 600);

                // #2
                SelectObject(hdc, ghBrush);
                SelectObject(hdc, ghPen);
                Rectangle(hdc, 0, 570, 800, 600);

                // #3->#11
                SelectObject(hdc, ohBrush);
                SelectObject(hdc, ohPen);
                Ellipse(hdc, 30, 30, 90, 90);
                DrawLine(hdc, 60, 5, 60, 25);
                DrawLine(hdc, 5, 60, 25, 60);
                DrawLine(hdc, 20, 20, 35, 35);
                DrawLine(hdc, 60, 95, 60, 115);
                DrawLine(hdc, 35, 85, 20, 100);
                DrawLine(hdc, 95, 60, 115, 60);
                DrawLine(hdc, 85, 35, 100, 20);
                DrawLine(hdc, 85, 85, 100, 100);

                //#12->#15
                SelectObject(hdc, bhBrush);
                Rectangle(hdc, 480, 330, 760, 570);
                Polygon(hdc, pt, 3);
                SelectObject(hdc, dbhBrush);
                SelectObject(hdc, dbhPen);
                Ellipse(hdc, 570, 390, 670, 490);
                Rectangle(hdc, 570, 440, 670, 570);

                //#16->#27
                SelectObject(hdc, lgrhBrush);
                SelectObject(hdc, dgrhPen);
                Rectangle(hdc, 160, 480, 290, 550);
                Rectangle(hdc, 170, 425, 240, 460);
                Polygon(hdc, pteo, 3);
                SelectObject(hdc, grhBrush);
                Ellipse(hdc, 210, 390, 310, 480);
                SelectObject(hdc, dgrhBrush);
                Ellipse(hdc, 160, 415, 180, 435);
                DrawLine(hdc, 170, 450, 190, 450);
                SelectObject(hdc, whBrush);
                Ellipse(hdc, 230, 405, 255, 430);
                SelectObject(hdc, blhBrush);
                SelectObject(hdc, blhPen);
                Ellipse(hdc, 231, 415, 245, 429);
                SelectObject(hdc, lgrhBrush);
                SelectObject(hdc, dgrhPen);
                Polygon(hdc, ptet, 3);
                SelectObject(hdc, dgrhBrush);
                SelectObject(hdc, dgrhPen);
                Polygon(hdc, ptt, 4);
                Polygon(hdc, ptpo, 3);
                Polygon(hdc, ptpt, 3);

                //#28->#31
                SelectObject(hdc, whBrush);
                SelectObject(hdc, whPen);
                Ellipse(hdc, 480, 60, 510, 90);
                Ellipse(hdc, 500, 40, 550, 90);
                Ellipse(hdc, 530, 50, 570, 90);
                Rectangle(hdc, 495, 75, 550, 90);

                // треугольник Серпинского вместо крыши
                SelectObject(hdc, lgrhBrush);
                SelectObject(hdc, dgrhPen);
                RecuTriangle(hdc, 620, 290, 40, 3);

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

BOOL DrawLine(HDC hdc, int x0, int y0, int x, int y) {
    MoveToEx(hdc, x0, y0, NULL);
    return LineTo(hdc, x, y);
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
