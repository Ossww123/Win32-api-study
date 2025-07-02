### 현재 구조의 문제점

- 한 델타 타임동안 발생한 일은 동시에 일어난 일이지만,
- 지금의 방식으로는 델타 타임 도중에 키 상태가 변경될 수 있어 원하지 않는 동작이 발생할 수 있다.

```
정상 작동

/* W키 누름 */

A 가 앞으로 간다.

B 가 앞으로 간다.

/* W키 뗌 */


잘못된 작동

/* W키 누름 */

A 가 앞으로 간다.

/* W키 뗌 */

B 는 멈춰 있다.
```

### 키 매니저

1. 프레임 동기화

   동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

2. 키 입력 이벤트 처리

   tab, hold, away


- 윈도우 포커싱 여부 조건 추가
```cpp
/* CKeyMgr.h */
#pragma once

#include "define.h"

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tab, hold, away


enum class KEY_STATE
{
	NONE, // 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAB, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 땐 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;		// 키의 상태값
	bool		bPrevPush;	// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}
};



/* CKeyMgr.cpp */
#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU, //ALT,
	VK_CONTROL, //CTRL,
	VK_LSHIFT, //LSHIFT,
	VK_SPACE, //SPACE,
	VK_RETURN, //ENTER,
	VK_ESCAPE, //ESC,

	//LAST,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::TAB;
				}

				m_vecKey[i].bPrevPush = true;
			}

			// 키가 안 눌려있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// 이전에도 눌려있었다.
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에 눌려있지 않았다.
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}
		}
	}

	// 윈도우 포커싱 해제 상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAB == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
	
}

```
