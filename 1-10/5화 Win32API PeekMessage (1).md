### Win32API 기본

```
현재 구조의 문제점

모든 물체들이 조금이라도 다시 그려져야 한다면 지웠다가 새로 그려야 한다.
이 '렌더링'과정을 어느 정도 하는가가 프레임을 결정. 보통 PC게임은 60프레임이 나와야 안정적으로 보인다.

완성된 장면만을 보여주지 않고 모든 장면을 보여주면서 깜빡이듯이 보이는 현상

메세지 기반으로 동작하기에 메세지가 없다면 동작하지 않는다.

```

```cpp
// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100, 100 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
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

            // Device Context 만들어서 ID 를 반환
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context (그리기)
            // DC 의 목적지는 hWnd
            // DC 의 펜은 기본펜(Black)
            // DC 의 브러쉬는 기본브러쉬(White)

            // 직접 펜과 브러쉬를 만들어서 DC 에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));  // 모르면 msdn 검색하기!
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0,0,255));
            //HBRUSH hBlueBrush = GetStockObject();                   // 자주 쓰는 브러쉬는 스톡오브젝트에 저장되어있다.

            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen);    // 원래 가지고 있던 디폴트 펜 반환
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);
            // SelectObject의 역할이 다양. 별도로 캐스팅을 해줘야 한다.

            // 변경된 펜으로 사각형 그림
            Rectangle(hdc
                , g_ptObjPos.x - g_ptObjScale.x / 2
                , g_ptObjPos.y - g_ptObjScale.y / 2
                , g_ptObjPos.x + g_ptObjScale.x / 2
                , g_ptObjPos.y + g_ptObjScale.y / 2);

            // DC 의 펜을 원래 펜으로 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 Red펜, Blue브러쉬 삭제 요청
            DeleteObject(hRedPen);
            DeleteObject(hBlueBrush);

            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)  // 부가적인 파라미터
        {
        case VK_UP:     // 윈도우에서는 키별로 매핑을 다 해놓음.

            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);  // 윈도우는 특정 창의 동작이 발생할 때 OS가 무효화 영역이 발생했다고 생각하고 WM_PAINT 발생
            // (윈도우, 무효화 영역 nullptr = 화면 전체, 이전 것들을 지울지 여부)

            break;

        case VK_DOWN:

            g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);

            break;

        case VK_LEFT:

            g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);

            break;

        case VK_RIGHT:

            g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);

            break;

        case 'W':       // 아스키 코드
        {
            int a = 0;
        }
            break;

        }
    }
        break;

    case WM_LBUTTONDOWN:
    {
        // lParam은 4바이트 정수형 자료형으로 각각 2바이트씩 마우스의 x, y좌표를 의미한다.
        // g_x = LOWORD(lParam);
        // g_y = HIWORD(lParam);
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


```
