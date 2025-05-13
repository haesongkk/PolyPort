#include "pch.h"
#include "World.h"

#include "GameObject.h"
#include "PlayerObject.h"
#include "CameraObject.h"
#include "DemoObject.h"

#include "Resource.h"
#include "D2DRenderer.h"

#include "PlayerObject.h"
#include "CameraObject.h"

#include "AnimationComponent.h"

#include "BitmapComponent.h"
#include "BubbleObject.h"
#include "TileImageComponent.h"
#include "ButtonComponent.h"
#include "CollisionManager.h"

#include "ButtonComponent.h"

#include "Debug.h"
#include "Load.h"
#include "Event.h"
#include "Input.h"

#include "GameProcess.h"
#include "PartSceneObject.h"
#include "CutSceneObject.h"
#include "DisappearingObject.h"
#include "MovingObject.h"
#include "PortObject.h"
#include "Sound.h"
#include "SpikeObject.h"
#include "MapTitleObject.h"

D2D1_MATRIX_3X2_F World::m_cameraTransform = {};


World::World()
    :m_gameObjects{}, m_pCameraObject{}
{
    m_pEvent = new Event(this);
    m_pLoad = new Load(this);

    m_pPlayerObject = new PlayerObject;
    m_pCameraObject = new CameraObject;

    // true 면 저장한 .json.json 파일 생성 (초기화)
    // false면 수정된 수치로 불러옴
    // true로 바꾸지 마시오!
    m_pLoad->CreatePlusDataMode(false);

    LoadAll();

    m_pLoad->Update();
    m_pEvent->Update();

    m_pPlayerObject->SetOwnerWorld(this);
    m_pCameraObject->SetOwnerWorld(this);

    m_gameObjects.push_back(m_pCameraObject);
    m_gameObjects.push_back(m_pPlayerObject);

    m_pCameraObject->SetFocusingObject(m_pPlayerObject);

    // 스테이지 1부터 시작하면 안됩!
    LoadScene(LOADSCENE::Title);
    //m_pPlayerObject->GetRootComponent()->SetRelativeTranslation({ 141440,7084 });
    //m_pCameraObject->GetRootComponent()->SetRelativeTranslation({ 141440,7084 });

}

World::~World()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        delete m_gameObjects[i];
    }
    delete m_pEvent;
    delete m_pLoad;
}

void World::Enter()
{
}

void World::Initialize()
{    
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Initialize();
    }

}

void World::Update(float dt)
{
    m_pEvent->Update();
    m_pLoad->Update();
 	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(dt);
	}
    CollisionManager::GetInstance()->Update();
    D2D1_MATRIX_3X2_F m_cameraMatrix=m_cameraTransform;
    D2D1InvertMatrix(&m_cameraMatrix);
    Input::GetInstance()->SetCameraVector({ m_cameraMatrix._31,m_cameraMatrix._32 });

    ForDebug();
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Render(pRenderTarget);
	}
}

void World::LateUpdate(float dt)
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->LateUpdate(dt);
    }
}

void World::Exit()
{
}

void World::SetFocus()
{
    if (m_pCameraObject == nullptr) return;
    if (m_pPlayerObject == nullptr) return;
    m_pCameraObject->SetFocusingObject(m_pPlayerObject);
}

void World::ForDebug()
{


    if (Input::GetInstance()->GetKeyState(KEY::SEVEN) == KEY_STATE::TAP)
        LoadScene(LOADSCENE::Stage1);

    if (Input::GetInstance()->GetKeyState(KEY::EIGHT) == KEY_STATE::TAP)
        LoadScene(LOADSCENE::Stage2);

    if (Input::GetInstance()->GetKeyState(KEY::NINE) == KEY_STATE::TAP)
        LoadScene(LOADSCENE::Stage3);

    if (Input::GetInstance()->GetKeyState(KEY::PLUS) == KEY_STATE::TAP)
    {
        Vector2D curSp = dynamic_cast<PlayerObject*>(m_pPlayerObject)->m_savepoint;
        for (auto i = 0; i < m_savePoints.size(); i++)
        {
            if (curSp == m_savePoints[i])
            {
                if (i + 1 != m_savePoints.size())
                {
                    m_pPlayerObject->GetRootComponent()->SetRelativeTranslation(m_savePoints[i + 1]);
                    if (m_savePoints[i + 1].x > 200000) m_scene = LOADSCENE::Stage3;
                    if (m_savePoints[i + 1].x < 200000) m_scene = LOADSCENE::Stage2;
                    return;
                }
                    
            }
        }
        m_pPlayerObject->GetRootComponent()->SetRelativeTranslation(m_savePoints[0]);
    }

    if (Input::GetInstance()->GetKeyState(KEY::MINUS) == KEY_STATE::TAP)
    {
        Vector2D curSp = dynamic_cast<PlayerObject*>(m_pPlayerObject)->m_savepoint;
        for (auto i = 0; i < m_savePoints.size(); i++)
        {
            if (curSp == m_savePoints[i])
            {
                if (i != 0)
                {
                    m_pPlayerObject->GetRootComponent()->SetRelativeTranslation(m_savePoints[i - 1]);
                    if (m_savePoints[i - 1].x > 200000) m_scene = LOADSCENE::Stage3;
                    if (m_savePoints[i - 1].x < 200000) m_scene = LOADSCENE::Stage2;
                }
            }
        }
    }

    POINT mouse = Input::GetInstance()->GetWorldMousePos();
    Debug::Text(L"mouse : " + to_wstring((int)mouse.x) + L", " + to_wstring((int)mouse.y));
}


void World::LoadNextScene()
{
    if (m_scene == LOADSCENE::Ending)
    {
        if (!m_bRealEnding) LoadScene(LOADSCENE::EndingA);
        else LoadScene(LOADSCENE::EndingB);
        return;
    }
    m_scene = (LOADSCENE)((UINT)m_scene + 1);
    LoadScene(m_scene);
}

void World::LoadScene(LOADSCENE _scene)
{
    m_scene = _scene;
    switch (_scene)
    {
        case LOADSCENE::Title:
        {
            Sound::Stop(BGM);
            Sound::Play(CHANNEL::BGM, "../Resource/sound/(loop)1.dont_title.wav");
            m_pLoad->LoadGameObjects("../Resource/worldData/title.json");
            break;
        }
        case LOADSCENE::Opening:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)2.meet_insert1.mp3");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Opening);
            break;
        }
        case LOADSCENE::Insert1:
        {
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Insert1);
            break;
        }
        case LOADSCENE::Stage1:
        {
            // 스테이지 1
            for (size_t i = 0; i < m_gameObjects.size(); i++)
            {
                m_gameObjects[i]->Regame();
            }
            m_bRealEnding = false;
            m_pPlayerObject->GetRootComponent()->SetRelativeTranslation({ 290,1051 });
            m_pCameraObject->GetRootComponent()->SetRelativeTranslation({ 1023,677 });

            
            GameObject* obj = CreateGameObject<MapTitleObject>();
            obj->GetComponent<UIComponent>("BitmapComponent")->SetBitmap(L"../Resource/image/maptitle/map_title_1.png");

            break;
        }
        case LOADSCENE::Insert2:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)4.samu_insert2.wav");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Insert2);
            break;
        }
        case LOADSCENE::Stage2:
        {
            m_pPlayerObject->GetRootComponent()->SetRelativeTranslation({ 135620,9370 });
            m_pCameraObject->GetRootComponent()->SetRelativeTranslation({ 136383,8933 });
            GameObject* obj = CreateGameObject<MapTitleObject>();
            obj->GetComponent<UIComponent>("BitmapComponent")->SetBitmap(L"../Resource/image/maptitle/map_title_2.png");
            break;
        }
        case LOADSCENE::Insert3:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)6.navi_insert3.mp3");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Insert3);
            break;
        }
        case LOADSCENE::Stage3:
        {
            m_pPlayerObject->GetRootComponent()->SetRelativeTranslation({ 263360,1947 });
            m_pCameraObject->GetRootComponent()->SetRelativeTranslation({ 264191,2016 });
            GameObject* obj = CreateGameObject<MapTitleObject>();
            obj->GetComponent<UIComponent>("BitmapComponent")->SetBitmap(L"../Resource/image/maptitle/map_title_3.png");
            break;
        }
        case LOADSCENE::Ending:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)7.rainy_ending.mp3");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Ending);
            break;
        }
        case LOADSCENE::EndingA:
        {
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::EndingA);
            break;
        }
        case LOADSCENE::EndingB:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)9.moon_hidden.mp3");
            Sound::Play(SFX, "../Resource/sound/break.wav");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::EndingB);
            break;
        }
        case LOADSCENE::Credit:
        {
            Sound::Stop(BGM);
            Sound::Play(BGM, "../Resource/sound/(loop)10.draw_credit.mp3");
            CutSceneObject* cut = Event::CreateObject<CutSceneObject>();
            cut->SetCutSceneType(CutScene::Credit);
            break;
        }
    }
}

void World::LoadAll()
{
    // 스테이지 1
    m_pLoad->LoadTileMapAt("../Resource/map/St1.json");
    m_pLoad->LoadPartSceneAt("../Resource/worldData/stage1_part.json");
    m_pLoad->LoadBackgroundAt("../Resource/worldData/stage1_background.json");
    m_pLoad->LoadGameObjects("../Resource/worldData/stage1_gameobjects.json");

    m_pLoad->LoadPartSceneAt("../Resource/worldData/map2_1_part.json", { 2115,129 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/stage2_2_part.json", { 2148,126 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/stage2_3_part.json", { 2180,116 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-4_part.json", { 2212,113 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-5_part.json", { 2180,95 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-6_part.json", { 2147,83 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-7_part.json", { 2114,83 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-8_part.json", { 2034,83 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-9_part.json", { 2001,83 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-10_part.json", { 2019,35 });
    m_pLoad->LoadPartSceneAt("../Resource/worldData/St2-11_part.json", { 2051,1 });

    m_pLoad->LoadTileMapAt("../Resource/map/St2-1.json", { 2115,129 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-2.json", { 2148,126 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-3.json", { 2180,116 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-4.json", { 2212,113 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-5.json", { 2180,95 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-6.json", { 2147,83 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-7.json", { 2114,83 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-8.json", { 2034,83 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-9.json", { 2001,83 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-10.json", { 2019,35 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-11.json", { 2051,1 });
    m_pLoad->LoadTileMapAt("../Resource/map/St2-11_Outline.json", { 2050,0 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/stage2_background.json", { 2000,0 });
    m_pLoad->LoadGameObjects("../Resource/worldData/stage2_gameobjects.json");

    //// 스테이지 3
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-1.json", { 4113,21 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-2.json", { 4148,20 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-3.json", { 4197,10 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-4.json", { 4148,2 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-5.json", { 4116,1 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-6.json", { 4084,1 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-7.json", { 4071,19 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-8.json", { 4033,12 });
    m_pLoad->LoadPartSceneAt("../Resource/part/St3-9.json", { 4001,1 });

    m_pLoad->LoadTileMapAt("../Resource/map/St3-1.json", { 4113,21 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-2.json", { 4148,20 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-3.json", { 4197,10 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-4.json", { 4148,2 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-5.json", { 4116,1 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-6.json", { 4084,1 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-7.json", { 4071,19 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-8.json", { 4033,12 });
    m_pLoad->LoadTileMapAt("../Resource/map/St3-9.json", { 4001,1 });

    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-1_bg.json", { 4113,21 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-2_bg.json", { 4148,20 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-3_bg.json", { 4197,10 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-4_bg.json", { 4148,2 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-5_bg.json", { 4116,1 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-6_bg.json", { 4084,1 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-7_bg.json", { 4071,19 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-8_bg.json", { 4033,12 });
    m_pLoad->LoadBackgroundAt("../Resource/worldData/St3-9_bg.json", { 4001,1 });

    m_pLoad->LoadBackgroundAt("../Resource/worldData/stage3_background.json", { 4000,0 });
    m_pLoad->LoadGameObjects("../Resource/worldData/stage3_gameObjects.json");

}
