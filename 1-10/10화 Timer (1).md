### Timer

- 픽셀의 단위는 정수이지만, 실수 데이터로 관리하는 것이 설계에 유용.
- 시간 동기화가 없다면 성능이 좋은 컴퓨터가 더 많은 명령을 실행하기에 실행횟수가 달라진다.
- 1프레임당 이동량 = 1초 이동량 \* 1프레임당 시간(Delta Time)
- Time Manager의 역할은 실시간으로 이 Delta Time을 계산해준다.
- 이 때 1000분의 1 단위의 GetTickCount()보다 정밀한 QueryPerformanceCounter()를 사용한다.
