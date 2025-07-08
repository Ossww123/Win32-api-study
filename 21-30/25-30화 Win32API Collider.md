### 오브젝트 설계
- 모든 오브젝트의 설계를 상속으로만 하면 '확장성'이 떨어질 수 있다.
- 컴포넌트 기반 설계를 통해 완화

- 오프셋 - 기준에서부터 상대적인 값


### 이전 프레임 정보
- 원하는 이벤트 발생을 위해서는 두 오브젝트간의 충돌에 관해 이전 프레임 정보가 필요
- 이때 씬의 오브젝트의  수 n에 따라 이전 프레임 정보가 매우 많을 수 있다.
- 그렇기 때문에 탐색에 용이한 자료구조가 필요
- 또 그런 자료구조를 위해 오브젝트 각각에 고유한 키값이 필요

### union
- 같은 메모리 공간을 여러가지 자료형으로 바라볼 수 있게 하는 키워드
```
typedef union _LARGE_INTERGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u
    LONGLONG QuarPart;
} LARGE_INTERGER;
```