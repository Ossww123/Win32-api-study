#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능

//class CCore
//{
//private:
//	static CCore* g_pInst;
//
//public:
//	static CCore* GetInstance()
//	{
//		// 최초 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//};

class CCore
{
SINGLE(CCore);

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	CCore();
	~CCore();
};
