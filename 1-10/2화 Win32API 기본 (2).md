### Win32API 기본

- windows 데스크톱 애플리케이션 프로젝트 생성

```
WCHAR

wchar_t 이름 재정의



#define MAX_LOADSTRING 100
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

문자 배열



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

전방 선언. 실제 구현은 아래에



UNREFERENCED_PARAMETER

참조되지 않는 파라미터, 아무 역할도 아님.



_In_, _In_opt_

윈도우 주석 언어, 변수의 의미를 나타냄, SAL 주석 이라고 함
**msdn 사이트 참고**



_In_ HINSTANCE hInstance

실행 된 프로세스의 시작 주소




_In_opt_ HINSTANCE hPrevInstance

이전에 실행 된 프로세스의 시작 주소
단, 가상 메모리를 사용하는 현재 윈도우는 모두 같은 시작 주소를 가진다
**가상 메모리**
각각 독립된 메모리를 사용하는 것처럼 메모리를 활용



_In_ LPWSTR    lpCmdLine

명령프롬프트 창에서 실행시 추가로 입력할 수 있는 문자열 포인터



// 전역 문자열을 초기화합니다.
LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
MyRegisterClass(hInstance);

테이블에서 ID에 해당하는 문자열 가져오기
기본 타이틀 초기화



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    ...

    return RegisterClassExW(&wcex);
}

WNDCLASSEXW 구조체 초기화 후
윈도우에서 제공하는 함수인 RegisterClassExW 함수 호출
**조직에서 효율적인 개발**
필요한 기능이 있다면 해당 조직에서 이미 이 기능이 구현되었는지 확인한다.
뭐든지 바닥부터 새로 만들수는 없음.



MyRegisterClass(hInstance);

윈도우 정보 등록



if (!InitInstance (hInstance, nCmdShow))
{
    return FALSE;
}

윈도우 생성. 실패시 프로그램 종료
**윈도우**
사용자와 프로그램이 상호작용 할 수 있는 인터페이스
프로세스와 윈도우는 같은 것이 아니다!



wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);

메뉴바 상태. nullptr로 하면 메뉴바가 없다는 뜻이다.



wcex.lpszClassName  = szWindowClass;

class(C++문법이 아닌 윈도우 정보)를 찾는 키값



HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

단축키 테이블 정보 로딩.
단축키 테이블이 존재.
if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
이 코드에서 단축키 테이블에 등록된 단축키가 사용되었는지 확인한다.



// 기본 메시지 루프입니다:
while (GetMessage(&msg, nullptr, 0, 0))
{
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

윈도우가 꺼지면 main함수가 꺼지게 된다.
**메세지 큐**
운영체제는 수많은 프로세스를 관리하게 되는데 이 때 메세지 큐에 메세지가 쌓인다.
그 중 포커싱 된 프로세스에 메세지들을 넣어주고 들어온 순서대로 해당 프로세스가 메세지들을 처리.
while 문을 돌면서 GetMessage를 통해 자신에게 도착한 메세지가 있는지 본다.
그리고 받은 msg 메세지를 처리
msg.hwnd는 메세지가 발생한 윈도우(하나의 프로세스가 여러 윈도우를 가질 수도 있다)
각 윈도우마다 "처리기 함수"를 가진다. (WndProc, 함수 포인터를 통해 전달)



WndProc 함수

윈도우의 수많은 메세지들 중 필요한 메세지들만 switch문 안에 있음.
그 외는 DefWindowProc(윈도우 제공 함수)로 처리



GetMessage 함수
메세지큐에서 메세지 확인할때까지 대기
"msg.message == WM_QUIT" 일 때 false를 반환한다. -> while 문이 종료된다(프로그램 종료)



**게임 개발**
지금의 메세지큐 방식으로는 게임 개발에 부적합



case WM_PAINT:

그리기 관련 메세지
Rectangle() 윈도우에서 제공하는 사각형 그리기 메세지



작업 영역
맨 왼쪽 좌상단이 (0, 0), 1의 단위는 픽셀
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
//
//
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
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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

**프로그램(Program)**  
저장장치(하드디스크, SSD 등)에 저장된 실행 가능한 코드 파일  
컴퓨터에 설치된 소프트웨어 자체를 의미

**프로세스(Process)**  
프로그램이 실제로 실행되어 메모리에 올라간 상태  
프로그램을 더블클릭해서 실행하면 그 순간부터 프로세스가 된다
