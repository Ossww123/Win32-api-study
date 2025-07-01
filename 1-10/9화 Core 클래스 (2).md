### 싱글톤 패턴

- 한 클래스의 객체의 생성을 1개로 제한한다.
- 어디서든 쉽게 접근 가능하다.
- 클래스의 생성자 접근 제어자를 private으로 지정.

- class내의 static 키워드
- 객체 없이도 클래스의 멤버 함수를 사용할 수 있게 한다. (정적 멤버 함수)
- 객체가 없으므로 this 키워드를 사용할 수 없고, 다른 멤버에 접근이 불가능하다.
- 단 static 키워드를 활용한 다른 정적 멤버는 접근 가능하다.
- 정적 멤버는 데이터 영역 메모리에 할당되고 클래스 안에서만 접근가능하다.
  - public 으로 선언시 다른곳에서도 접근 가능하다.
- 정적 멤버는 클래스 밖에서 반드시 초기화를 해주어야 한다. (X 링크 에러)

### 매크로 함수

```
#define ADD(a, b)	(a + b)
```

함수를 구현하는 것이 아니라 치환해준다는 것에 주의

```
#define ADD(a, b)	a + b

int a = 10 * ADD(10, 20)  // 10 * 10 + 20
```

### 미리 컴파일된 헤더

- 속성 - C/C++ - 미리 컴파일된 헤더 - 만들기(/Yc)
- 모든 cpp 파일에 해당 헤더파일이 포함되어야 함
- 완성된 코드들. 컴파일할 필요가 없는 코드들.

### 렌더링
- 매 프레임마다 완성된 장면을 보여준다.


```cpp
int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0, 0,m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);		// 윈도우 설정에 따라 rt값 조정
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	return S_OK;
}
```
