# PolyPort

**PolyPort**는 게임인재원 5기 Direct2D 팀 프로젝트로 제작된 2D 퍼즐 플랫폼 게임입니다.

플레이어는 스테이지를 이동하며 발판, 장애물, 아이템, 포트, 버블 등 다양한 오브젝트와 상호작용합니다.  
프로젝트는 단순히 게임 로직만 구현한 것이 아니라, Direct2D 기반의 자체 2D 게임 엔진 구조를 만들고 그 위에서 게임을 동작시키는 방식으로 구성되어 있습니다.

엔진 내부에는 게임 오브젝트, 컴포넌트, 렌더링, 입력, 충돌, 사운드, FSM, 씬 로딩, 디버그 기능 등이 분리되어 있으며, 별도의 툴 프로젝트를 통해 맵과 오브젝트 데이터를 제작·관리할 수 있도록 구성했습니다.

## 실행 화면

[![](https://img.youtube.com/vi/jdqNjF8CTdQ/0.jpg)](https://www.youtube.com/watch?v=jdqNjF8CTdQ)

## 주요 기능

### 2D 퍼즐 플랫폼 플레이

플레이어는 2D 스테이지 안에서 이동, 점프, 착지, 장애물 회피 등의 기본 플랫폼 액션을 수행합니다.  
스테이지 곳곳에 배치된 지형과 오브젝트를 활용해 목표 지점까지 진행하는 구조입니다.

### 포트 상호작용

플레이어는 맵에 배치된 포트 오브젝트와 상호작용할 수 있습니다.  
가까운 포트를 인식하고 활성화하여 이동이나 퍼즐 진행에 활용할 수 있습니다.

### 버블 및 특수 오브젝트

버블, 이동 발판, 사라지는 발판, 가시, 젬 등 다양한 오브젝트가 스테이지에 배치되어 있습니다.  
각 오브젝트는 플레이어의 이동 방식이나 스테이지 진행 방식에 영향을 줍니다.

### 스테이지 진행

타이틀, 오프닝, 스테이지, 엔딩 등 여러 씬으로 게임 흐름이 구성되어 있습니다.  
플레이어는 스테이지를 클리어하면서 다음 구간으로 이동할 수 있습니다.

### 저장 지점 기능

스테이지 내 특정 위치를 저장 지점으로 사용할 수 있습니다.  
플레이어가 사망하거나 특정 상황이 발생했을 때 저장된 위치를 기준으로 다시 시작할 수 있습니다.

### 사운드 재생

게임 진행 중 배경음악과 효과음이 재생됩니다.  
스테이지, 이벤트, 상호작용 상황에 따라 사운드를 통해 게임의 분위기와 피드백을 제공합니다.

### 제작 툴을 활용한 맵 구성

별도의 툴을 사용해 타일, 오브젝트, 콜라이더 등을 배치하고 저장할 수 있습니다.  
이를 통해 게임 스테이지를 데이터 기반으로 제작하고 수정할 수 있습니다.

## 구현 상세

### Direct2D 기반 렌더링 시스템

`D2DRenderer`를 중심으로 Direct2D, DirectWrite, WIC 객체를 초기화하고 관리합니다.  
이미지 리소스는 WIC를 통해 로드한 뒤 Direct2D 비트맵으로 변환하여 렌더링에 사용합니다.

각 게임 오브젝트는 렌더링 컴포넌트를 통해 화면에 출력되며, 월드에서 오브젝트 목록을 순회하면서 프레임 단위로 렌더링을 수행합니다.

### 컴포넌트 기반 오브젝트 구조

게임 오브젝트는 `GameObject`를 기반으로 구성되며, 기능별 처리는 컴포넌트로 분리되어 있습니다.  
렌더링, 충돌, 애니메이션, 카메라, 물리 처리 등을 각각 컴포넌트로 관리하여 오브젝트별 기능을 조합할 수 있도록 구현했습니다.

이를 통해 플레이어, 포트, 버블, 젬, 가시, 이동 발판 등 서로 다른 오브젝트를 동일한 기본 구조 안에서 관리할 수 있습니다.

### 월드 및 씬 관리 구조

`World`는 게임 오브젝트 생성, 갱신, 렌더링, 씬 전환을 관리합니다.  
타이틀, 오프닝, 스테이지, 엔딩 등 씬 상태에 따라 필요한 오브젝트와 리소스를 생성하고 갱신합니다.

씬 로딩은 enum 값을 기준으로 분기되며, 각 씬에 맞는 맵 데이터와 배경음악, 컷신 오브젝트 등을 초기화하는 방식으로 구성되어 있습니다.

### 입력 처리 구조

`Input` 클래스는 키보드와 마우스 입력 상태를 관리합니다.  
키 입력은 누름, 유지, 해제 상태로 구분되며, 플레이어 이동, 점프, 디버그 기능, 테스트용 씬 이동 등에 사용됩니다.

입력 처리를 별도 클래스로 분리하여 게임 로직에서 직접 Win32 입력 처리를 다루지 않도록 구성했습니다.

### 충돌 처리 시스템

`CollisionManager`는 게임 내 콜라이더들을 그룹 단위로 관리하고, 필요한 그룹 간 충돌만 검사합니다.  
충돌 판정은 AABB와 OBB 기반으로 처리되며, 오브젝트의 충돌 형태에 따라 적절한 방식을 사용합니다.

충돌 결과는 `OnCollisionEnter`, `OnCollisionStay`, `OnCollisionExit` 형태의 이벤트로 전달됩니다.  
이를 통해 착지 판정, 이동 보정, 아이템 획득, 저장 지점 갱신, 씬 전환 등의 게임 로직을 처리합니다.

### FSM 기반 플레이어 상태 관리

플레이어의 상태는 FSM 구조를 통해 관리됩니다.  
이동, 착지, 사망, 버블 진입, 텔레포트 등 상태별 동작을 분리하여 구현했습니다.

상태 변화에 따라 플레이어의 이동 로직, 애니메이션, 충돌 반응이 달라지도록 구성되어 있습니다.

### JSON 기반 데이터 로딩

`Load` 클래스는 JSON 파일을 읽어 맵과 오브젝트 데이터를 생성합니다.  
타일맵, 배경, 포트, 가시, 젬, 이동 발판, 사라지는 발판 등의 정보를 외부 데이터에서 읽어 실제 게임 오브젝트로 변환합니다.

이를 통해 스테이지 배치 정보를 코드에 직접 작성하지 않고, 데이터 파일을 수정하여 맵을 구성할 수 있도록 구현했습니다.

### FMOD 기반 사운드 관리

`Sound` 클래스는 FMOD를 이용해 BGM과 효과음을 로드하고 재생합니다.  
사운드는 루프 여부에 따라 배경음악과 효과음으로 구분되며, 게임 씬이나 이벤트 상황에 맞춰 재생됩니다.

### 제작 툴 구조

`TOOL` 프로젝트는 맵 제작을 보조하기 위한 별도 툴 프로젝트입니다.  
이미지 팔레트, 타일 버튼, 콜라이더 윈도우, 오브젝트 윈도우, 저장/불러오기 창 등으로 구성되어 있습니다.

툴에서 제작한 데이터는 JSON 형태로 저장되며, 게임 실행 시 엔진에서 해당 데이터를 읽어 스테이지를 구성합니다.

## 기술 스택

| 구분 | 내용 |
| --- | --- |
| Language | C++, C |
| Graphics | Direct2D, DirectWrite, WIC |
| Platform | Windows |
| IDE / Build | Visual Studio, MSVC v143 |
| Data Format | JSON |
| JSON Library | nlohmann/json |
| Sound | FMOD |
| Architecture | Component-based GameObject, FSM, Scene System |
| Tool | Win32/MFC 기반 제작 툴 프로젝트 |

## 프로젝트 구조

```text
PolyPort/
├── 2Q_Engine.sln
├── 2Q_Engine/
│   ├── 2Q_Engine.cpp
│   ├── GameProcess.cpp / .h
│   ├── World.cpp / .h
│   ├── GameObject.cpp / .h
│   ├── Component.cpp / .h
│   ├── D2DRenderer.cpp / .h
│   ├── Input.cpp / .h
│   ├── CollisionManager.cpp / .h
│   ├── AABB.cpp / .h
│   ├── OBB.cpp / .h
│   ├── Collider.cpp / .h
│   ├── BoxCollider.cpp / .h
│   ├── RigidBody.cpp / .h
│   ├── FSM.cpp / .h
│   ├── FSMComponent.cpp / .h
│   ├── FSMCharacter.cpp / .h
│   ├── AnimationComponent.cpp / .h
│   ├── AnimationAsset.cpp / .h
│   ├── BitmapComponent.cpp / .h
│   ├── CameraObject.cpp / .h
│   ├── CameraComponent.cpp / .h
│   ├── PlayerObject.cpp / .h
│   ├── PortObject.cpp / .h
│   ├── BubbleObject.cpp / .h
│   ├── GemObject.cpp / .h
│   ├── SpikeObject.cpp / .h
│   ├── MovingObject.cpp / .h
│   ├── DisappearingObject.cpp / .h
│   ├── CutSceneObject.cpp / .h
│   ├── Event.cpp / .h
│   ├── Load.cpp / .h
│   ├── Sound.cpp / .h
│   └── Debug.cpp / .h
│
├── Demo/
│   ├── Demo.cpp
│   ├── Demo.vcxproj
│   └── pch.h
│
└── TOOL/
    ├── TOOL.cpp / .h
    ├── MainFrm.cpp / .h
    ├── MainWin.cpp / .h
    ├── ToolManager.cpp / .h
    ├── ImagePalette.cpp / .h
    ├── TileButton.cpp / .h
    ├── ColliderWindow.cpp / .h
    ├── ColliderPalette.cpp / .h
    ├── ObjWin.cpp / .h
    ├── PathWindow.cpp / .h
    ├── SaveWindow.cpp / .h
    ├── LoadWindow.cpp / .h
    └── NewWindow.cpp / .h
