# GasolinnEngine

SDL2를 이용해 작성된 2D게임 프레임워크

## 1.Engine
SDL함수들 초기화 FPS및 화면크기 등 기본설정을 하고 게임루프를 실행
## 2.System
기본적인 구조를 유지하기 위한 속성들을 가진 클래스
## 3.Scene
한 화면을 구성하는 Scene. Object를 추가하거나 다른 Scene으로 바꿀 수 있다. 여러개의 Scene을 동시 출력가능
## 4.Object 
Scene안에 들어가는 이동체 사용자는 Object를 상속받아서 게임 구성요소를 구현할 수 있다.
## 5.Collider
Object 내부에 추가할 수 있는 BoundingBox를 가지고 있는 충돌체. 추가한 충돌체끼리는
원, AB사각형, OBB사각형 충돌판정을한다.
## 6.Camera
화면을 보는 초점을 확대,축소,이동할 수 있는 스태틱 클래스
## 7.Function
Timer, Vector, String, Math 관련 도움을 줄 수 있는 클래스들을 가지고 있는 namespace
## 8.ResourceManager
음악, 이미지 등을 자동으로 로드해서 관리해주는 클래스