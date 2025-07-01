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

```cpp
class CCore
{
private:
	static CCore* g_pInst;

public:
	static CCore* GetInstance()
	{
		// 최초 호출 된 경우
		if (nullptr == g_pInst)
		{
			g_pInst = new CCore;
		}

		return g_pInst;
	}

	static void Release()
	{
		if (nullptr != g_pInst)
		{
			delete g_pInst;
			g_pInst = nullptr;
		}
	}

private:
	CCore();
	~CCore();
};
```
