#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    virtual void update();
    virtual void Enter();   // 명시적으로 virtual 키워드 넣기
    virtual void Exit();    // 없어도 됨

public:
    CScene_Start();
    ~CScene_Start();
};
