# PolyPort

> 코드 기록용으로 업로드한 리포지토리입니다.  
> 리소스 및 외부 라이브러리는 포함하지 않습니다.  
> 프로젝트를 실행할 수 없습니다.  

## 📌 프로젝트 개요
독창적인 점프와 순간이동 액션을 활용해 아이템을 모아 클리어 조건을 달성하는 플랫포머 게임


### 🛠 개발 환경
- Language: `C++17`
- Libraries: `Win32 API`, `Direct2D`, `FMOD`, `nlohmann/json`, `DirectWrite`, `WIC (Windows Imaging Component)`, `COM (Component Object Model)`, `DirectXMath`, `DirectXCollision`, `DXGI`
- Platform: `Window 11`, `visual studio 2022`

### 🔗 리소스 출처
- 아트 리소스: 게임인재원 5기 아트반 (2명)
- 그 외: 기획자 서치

---

## 🔍 결과물

[![시연 영상](https://img.youtube.com/vi/jdqNjF8CTdQ/0.jpg)](https://www.youtube.com/watch?v=jdqNjF8CTdQ)

다운로드: [https://store.onstove.com/ko/games/2344](https://store.onstove.com/ko/games/2344)

---

## 🔧 개선사항
- 타일맵툴을 개발했지만 기능이 제한적이라 불편한 점이 많았다.
- 게임 실행 시 로딩이 너무 길고, 로딩 화면도 없다.
- 실행 중 가끔 터지는데 아직 원인을 찾지 못했다...
- 컴포넌트 기반을 목표로 하였으나 점점 오브젝트 기반이 되었다.
- 엔진과 게임 프로젝트를 분리하려고 했지만 무의미해졌다. (전부 엔진에서 구현함)
