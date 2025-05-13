#include "pch.h"
#include "Load.h"

#include "World.h"
#include "PlayerObject.h"


#include "ButtonComponent.h"
#include "TileImageComponent.h"
#include "TileColliderComponent.h"

#include "CameraObject.h"
#include "Debug.h"
#include "TileObject.h"
#include "CollisionManager.h"
#include "BitmapComponent.h"
#include "TextComponent.h"
#include "Sound.h"
#include "PartSceneObject.h"
#include "Event.h"
#include "ButtonObject.h"
#include "BubbleObject.h"
#include "PortObject.h"
#include "GemObject.h"
#include "SpikeObject.h"
#include "MovingObject.h"


#include <istream>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>
#include "MapTitleObject.h"
#include "DisappearingObject.h"

using json = nlohmann::json;

World* Load::m_pWorld = nullptr;

vector<string> Load::m_gameobjectsPath = {};
vector<POINT> Load::m_gameobjectsAt = {};

vector<string> Load::m_tilemapPath = {};
vector<POINT> Load::m_tilemapAt = {};

vector<string> Load::m_partScenePath = {};
vector<POINT> Load::m_partSceneAt = {};

vector<string> Load::m_bgPath = {};
vector<POINT> Load::m_bgAt = {};


Load::Load(World* _pWorld)
{
    m_pWorld = _pWorld;

    std::ifstream file(L"../Resource/worldData/spData.json");
    assert(file.is_open());

    json saveData;
    file >> saveData;

    for (const auto& sd : saveData)
    {
        m_pWorld->SavePoints().push_back({ sd["savePoint"][0], sd["savePoint"][1] });
    }
    
}

void Load::Update()
{
    if (m_gameobjectsPath.size() != 0)
    {
        //CollisionManager::GetInstance()->Clear();
    }
    for (int i = 0; i < m_bgPath.size(); i++)
    {
        LoadBackgroundOnUpdate(m_bgPath[i], m_bgAt[i]);
    }
    for (int i = 0; i < m_tilemapPath.size(); i++)
    {
        LoadTileMapOnUpdate(m_tilemapPath[i], m_tilemapAt[i]);
    }
    for (int i = 0; i < m_partScenePath.size(); i++)
    {
        LoadPartSceneOnUpdate(m_partScenePath[i], m_partSceneAt[i]);
    }
    for (int i = 0; i < m_gameobjectsPath.size(); i++)
    {
        LoadGameObjectsOnUpdate(m_gameobjectsPath[i], m_gameobjectsAt[i]);
    }

    if (m_gameobjectsPath.size() != 0)
    {
        //m_pWorld->Initialize();
    }

    m_gameobjectsPath.clear();

    m_tilemapPath.clear();
    m_tilemapAt.clear();

    m_partScenePath.clear();
    m_partSceneAt.clear();

    m_bgPath.clear();
    m_bgAt.clear();
}

void Load::LoadGameObjects(string _path, POINT _at)
{
    m_gameobjectsPath.push_back(_path);
    m_gameobjectsAt.push_back(_at);
}

void Load::LoadTileMapAt(string _path, POINT _at)
{
    m_tilemapPath.push_back(_path);
    m_tilemapAt.push_back(_at);
}

void Load::LoadPartSceneAt(string _path, POINT _at)
{
    m_partScenePath.push_back(_path);
    m_partSceneAt.push_back(_at);
}

void Load::LoadBackgroundAt(string _path, POINT _at)
{
    m_bgPath.push_back(_path);
    m_bgAt.push_back(_at);
}

void Load::LoadGameObjectsOnUpdate(string _path, POINT _at)
{
    std::ifstream file(_path);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    for (const auto& obj_data : world_data)
    {
        GameObject* obj = nullptr;

        if (obj_data.contains("name"))
        {
            string name = obj_data["name"];
          
            if (name == "port")
            {
                obj = m_pWorld->CreateGameObject<PortObject>();
                int index = 0;
                float x = obj_data["root"][index++];
                float y = obj_data["root"][index++];
                float rot = obj_data["root"][index++];
                float dx = obj_data["root"][index++];
                float dy = obj_data["root"][index++];

                obj->GetRootComponent()->SetRelativeTranslation({ x,y });
                obj->GetRootComponent()->SetRelativeRotation(rot);
                obj->GetRootComponent()->SetRelativeScale({ dx,dy });
                continue;
            }
            if (name == "spike")
            {
                obj = m_pWorld->CreateGameObject<SpikeObject>();
                obj->GetComponent<BitmapComponent>("BitmapComponent")->SetBitmap(L"");
            }
            if (name == "gem")
            {
                obj = m_pWorld->CreateGameObject<GemObject>();
                int index = 0;
                float x = obj_data["gem"][index++];
                float y = obj_data["gem"][index++];
                dynamic_cast<GemObject*>(obj)->SetConnectedObject({ x, y });
            }
            if (name == "move")
            {
                int index = 0;
                float startX = obj_data["move"][index++];
                float startY = obj_data["move"][index++];
                float EndX = obj_data["move"][index++];
                float EndY = obj_data["move"][index++];
                int size = obj_data["move"][index++];

                obj = m_pWorld->CreateGameObject<MovingObject>();
                dynamic_cast<MovingObject*>(obj)->SetStartingPos({ startX,startY });
                dynamic_cast<MovingObject*>(obj)->SetEndingPos({ EndX,EndY });
                dynamic_cast<MovingObject*>(obj)->SetSize(size);

                index = 0;
                float x = obj_data["root"][index++] + TileSize / 2;
                float y = obj_data["root"][index++] + TileSize / 2;
                obj->GetRootComponent()->SetRelativeTranslation({ x,y });
                continue;
            }
            
            if (obj == nullptr)
            {
                obj = m_pWorld->CreateGameObject<GameObject>();
                obj->SetTag(name);
            }

            if (obj_data.contains("root"))
            {
                int index = 0;
                float x = obj_data["root"][index++] + _at.x * TileSize;
                float y = obj_data["root"][index++] + _at.y * TileSize;
                float rot = obj_data["root"][index++];
                float dx = obj_data["root"][index++];
                float dy = obj_data["root"][index++];

                obj->GetRootComponent()->SetRelativeTranslation({ x,y });
                obj->GetRootComponent()->SetRelativeRotation(rot);
                obj->GetRootComponent()->SetRelativeScale({ dx,dy });
            }
            if (obj_data.contains("boxCollider"))
            {
                int index = 0;
                float dx = obj_data["boxCollider"][index++];
                float dy = obj_data["boxCollider"][index++];
                BoxCollider* boxCollider = obj->AddComponent<BoxCollider>("boxCollider");
                boxCollider->SetExtends(dx,dy);

                if (obj->GetTag() == "gem" || obj->GetTag() == "item")
                    boxCollider->SetColliderGroup(ColliderGroup::ITEM);

                if (obj->GetTag() == "next"|| obj->GetTag()=="savePoint")
                    boxCollider->SetColliderGroup(ColliderGroup::SAVEPOINT);
                
                CollisionManager::GetInstance()->AddCollider(boxCollider);
            }
            if (obj_data.contains("bitmap"))
            {
                string str = obj_data["bitmap"];
                wstring bitmapKey;
                bitmapKey.assign(str.begin(), str.end());

                BitmapComponent* bitmap = obj->AddComponent<BitmapComponent>("bitmap");
                bitmap->SetBitmap(bitmapKey);
            }
           
            if (obj_data.contains("button"))
            {
                Event::DeleteObject(obj);

                obj = Event::CreateObject<ButtonObject>();
                obj->SetTag(obj_data["name"]);
                int index = 0;
                string sDefault = obj_data["button"][index++];
                string sActive = obj_data["button"][index++];
                float x = obj_data["button"][index++];
                float y = obj_data["button"][index++];
                float dx = obj_data["button"][index++];
                float dy = obj_data["button"][index++];

                wstring wDefault, wActive;
                wDefault.assign(sDefault.begin(), sDefault.end());
                wActive.assign(sActive.begin(), sActive.end());

                ButtonComponent* button = obj->AddComponent<ButtonComponent>("button");
                button->SetActiveBitmap(wActive);
                button->SetDefaultBitmap(wDefault);
                button->SetButtonRect(x, y, dx, dy);
            }
            if (obj_data.contains("ui"))
            {
                int index = 0;
                string tmp = obj_data["ui"][index++];
                float x = obj_data["ui"][index++];
                float y = obj_data["ui"][index++];

                wstring bitmapKey;
                bitmapKey.assign(tmp.begin(), tmp.end());

                UIComponent* ui = obj->AddComponent<UIComponent>("ui");
                ui->SetBitmap(bitmapKey);
                ui->SetRelativeTranslation({ x,y });
            }
            if (obj_data.contains("animation"))
            {
                int index = 0;
                string asset = obj_data["animation"][index++];
                string state = obj_data["animation"][index++];

                wstring wAsset;
                wAsset.assign(asset.begin(), asset.end());

                AnimationComponent* anim = obj->AddComponent<AnimationComponent>("animation");
                anim->SetAnimationAsset(wAsset);
                anim->SetAnimation(state, false, true);
            }
        }
    }
    m_pWorld->SetFocus();

    file.close();
}

void Load::LoadTileMapOnUpdate(string _path, POINT _at)
{
    std::ifstream file(_path);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    json plus_data; // 젬, 이동형구름, 폴리포트 정보를 담을 파일
    json sp_data; // 스폰 포인트 담아놓을 곳

    std::ifstream existing_file(L"../Resource/worldData/spData.json");
    if (existing_file.is_open())
    {
        existing_file >> sp_data;
        existing_file.close();
    }

    for (const auto& obj_data : world_data)
    {
        int imageIndex = 0;
        std::string data = obj_data["tileImage"][imageIndex++];

        // 기본이미지가 들어가있거나 이미지가 없으면 오브젝트를 생성하지 않는다
        if (data == "../Resource/tile/default.jpg") continue;
        if (data == "../Resource/tile\\default.jpg") continue;
        if (data == "") continue;

        json j = obj_data;

        int x = obj_data["tileImage"][imageIndex++] + _at.x;
        int y = obj_data["tileImage"][imageIndex++] + _at.y;

        std::wstring tmp;
        tmp.assign(data.begin(), data.end());

        GameObject* obj = m_pWorld->CreateGameObject<TileObject>();
        TileImageComponent* tileImage = obj->AddComponent<TileImageComponent>("tileImage");
        tileImage->SetBitmap(tmp);
        tileImage->SetTilePos({ x,y });


        if (obj_data.contains("tileCollider"))
        {
            int colliderIndex = 0;
            POINT leftTop, rightBottom;
            leftTop.x = obj_data["tileCollider"][colliderIndex++] + _at.x;
            leftTop.y = obj_data["tileCollider"][colliderIndex++] + _at.y;
            rightBottom.x = obj_data["tileCollider"][colliderIndex++] + _at.x;
            rightBottom.y = obj_data["tileCollider"][colliderIndex++] + _at.y;

            TileColliderComponent* tileCollider = obj->AddComponent<TileColliderComponent>("tileCollider");
            tileCollider->SetTileColliderVertex(leftTop, rightBottom);

            if (tmp == L"../Resource/tile\\bubble4.png")
            {
                // 버블
                DeleteTiles(obj);
                BubbleObject* bo = m_pWorld->CreateGameObject<BubbleObject>();
                bo->GetRootComponent()->SetRelativeTranslation({ (float)rightBottom.x * TileSize,(float)rightBottom.y * TileSize });
            }
            else if (tmp == L"../Resource/tile\\polyport.png" || tmp == L"../Resource/tile\\polyport_4.png")
            {
                // 포트
                DeleteTiles(obj);

                if (m_bCreatePlus)
                {
                    json plus_obj;
                    plus_obj["name"] = "port";
                    plus_obj["root"] =
                    {
                        rightBottom.x * TileSize,
                        rightBottom.y * TileSize,
                        0,1,1
                    };
                    plus_data.push_back(plus_obj);
                }
            }
            else if (tmp == L"../Resource/tile\\respawn.png")
            {
                // 세이브 포인트
                obj->SetTag("savePoint");
                tileCollider->SetColliderGroup(ColliderGroup::SAVEPOINT);
                tileCollider->SetCollisionType(CollisionType::UNBLOCK);
                CollisionManager::GetInstance()->AddCollider(tileCollider);
                json sp;
                sp["savePoint"] =
                {
                    (leftTop.x + rightBottom.x + 1) * TileSize / 2,
                    (leftTop.y + rightBottom.y + 1) * TileSize / 2
                };
                sp_data.push_back(sp);

            }
            else if (tmp == L"../Resource/tile\\tile05.png")
            {
                // 젬이랑 연결될 구름
                obj->SetTag("gemConnect");
                tileCollider->SetColliderGroup(ColliderGroup::GROUND);
                CollisionManager::GetInstance()->AddCollider(tileCollider);
            }
            else if (tmp == L"../Resource/tile\\gem.png")
            {
                // 젬 ... 연결된 장애물 지정해줘야 해서 직접 생성함
                DeleteTiles(obj);
                if (m_bCreatePlus)
                {
                    json plus_obj;
                    plus_obj["name"] = "gem";
                    plus_obj["root"] =
                    {
                        rightBottom.x * TileSize + TileSize / 2,
                        rightBottom.y * TileSize + TileSize / 2,
                        0,1,1
                    };
                    plus_obj["gem"] =
                    {
                        rightBottom.x * TileSize + TileSize / 2,
                        rightBottom.y * TileSize + TileSize / 2
                    };
                    plus_data.push_back(plus_obj);
                }
            }
            else if (tmp == L"../Resource/tile\\item.png")
            {
                // 구슬 조각
                obj->SetTag("item");
                tileCollider->SetColliderGroup(ColliderGroup::ITEM);
                tileCollider->SetCollisionType(CollisionType::UNBLOCK);
                CollisionManager::GetInstance()->AddCollider(tileCollider);
            }
            else if (tmp == L"../Resource/tile\\cloud_b_03.png")
            {
                // 이동형 + 그냥 구름
                DeleteTiles(obj);
                if (m_bCreatePlus)
                {
                    json plus_obj;
                    plus_obj["name"] = "move";
                    plus_obj["root"] =
                    {
                        (leftTop.x + rightBottom.x + 1) / 2 * TileSize,
                        (leftTop.y + rightBottom.y + 1) / 2 * TileSize,
                        0,1,1
                    };
                    plus_obj["move"] =
                    {
                        (leftTop.x + rightBottom.x + 1) / 2 * TileSize,
                        (leftTop.y + rightBottom.y + 1) / 2 * TileSize,
                        (leftTop.x + rightBottom.x + 1) / 2 * TileSize,
                        (leftTop.y + rightBottom.y + 1) / 2 * TileSize,
                        rightBottom.x - leftTop.x + 1
                    };
                    plus_data.push_back(plus_obj);
                }
            }
            else if (tmp == L"../Resource/tile\\cloud_p_03.png")
            {
                // 스프링 구름
                obj->SetTag("spring");
                tileCollider->SetCollisionType(CollisionType::ONEWAY);
                CollisionManager::GetInstance()->AddCollider(tileCollider);

            }
            else if (tmp == L"../Resource/tile\\cloud_y_03.png")
            {
                // 사라지는 구름
                DeleteTiles(obj);
                obj = m_pWorld->CreateGameObject<DisappearingObject>();
                dynamic_cast<DisappearingObject*>(obj)->SetSize(rightBottom.x - leftTop.x + 1);
                obj->GetRootComponent()->SetRelativeTranslation({ (leftTop.x + rightBottom.x + 1) / 2.f * TileSize,
                    (leftTop.y + rightBottom.y + 1) / 2.f * TileSize
                    });
                
            } 
            else if (tmp == L"../Resource/tile\\spike.png"
                ||tmp == L"../Resource/tile\\spike_03.png"
                ||tmp == L"../Resource/tile\\spike2.png"
                ||tmp == L"../Resource/tile\\spike2_03.png"
                || tmp == L"../Resource/tile\\spike_02.png"
                || tmp == L"../Resource/tile\\spike_04.png"
                || tmp == L"../Resource/tile\\spike2_02.png"
                || tmp == L"../Resource/tile\\spike2_04.png"
                || tmp == L"../Resource/tile\\sp.png")
            {
                DeleteTiles(obj);
                for (int i = leftTop.x; i <= rightBottom.x; i++)
                {
                    for (int j = leftTop.y; j <= rightBottom.y; j++)
                    {
                        SpikeObject* so = m_pWorld->CreateGameObject<SpikeObject>();
                        so->GetRootComponent()->SetRelativeTranslation({ (float)i * TileSize + TileSize / 2,(float)j * TileSize + TileSize / 2 });
                        so->GetComponent<BitmapComponent>("BitmapComponent")->SetBitmap(tmp);
                    }
                }
            }
           
            else
            {
                obj->SetTag("fixedPlatform");
                tileCollider->SetColliderGroup(ColliderGroup::GROUND);
                CollisionManager::GetInstance()->AddCollider(tileCollider);
            }

        }
    }

   

    //std::ofstream spFile{ L"../Resource/worldData/spData.json"};
    //assert(spFile.is_open());

    //spFile << sp_data.dump(2);
    //spFile.close();




    if (m_bCreatePlus)
    {
        std::ofstream plusfile{ _path + ".json" };
        assert(plusfile.is_open());

        plusfile << plus_data.dump(2);
        plusfile.close();
    }
    else 
        LoadGameObjectsOnUpdate(_path + ".json");
}

void Load::LoadPartSceneOnUpdate(string _path, POINT _at)
{
    std::ifstream file(_path);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    json tp;

    for (const auto& obj_data : world_data)
    {
        if (obj_data.contains("tileCollider"))
        {
            int index = 0;
            POINT leftTop, rightBottom;
            leftTop.x = obj_data["tileCollider"][index++] + _at.x;
            leftTop.y = obj_data["tileCollider"][index++] + _at.y;
            rightBottom.x = obj_data["tileCollider"][index++] + _at.x;
            rightBottom.y = obj_data["tileCollider"][index++] + _at.y;

            Vector2D fLeftTop, fRightBottom;
            fLeftTop.x = leftTop.x * TileSize - 1;
            fLeftTop.y = leftTop.y * TileSize - 1;
            fRightBottom.x = (rightBottom.x + 1) * TileSize + 1;
            fRightBottom.y = (rightBottom.y + 1) * TileSize + 1;

            float dx = fRightBottom.x - fLeftTop.x;
            float dy = fRightBottom.y - fLeftTop.y;
            Vector2D pos = (fRightBottom + fLeftTop) / 2;

            tp.push_back(obj_data);
            PartSceneObject* obj = m_pWorld->CreateGameObject<PartSceneObject>();
            obj->GetComponent<BoxCollider>("BoxCollider")->SetExtends(dx / 2, dy / 2);
            obj->GetRootComponent()->SetRelativeTranslation(pos);
            

        }

    }
    std::ofstream tf{ _path };
    assert(tf.is_open());

    tf << tp.dump(2);
    tf.close();

}

void Load::LoadBackgroundOnUpdate(string _path, POINT _at)
{
    std::ifstream file(_path);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    json plus_data; // 젬, 이동형구름, 폴리포트 정보를 담을 파일

    for (const auto& obj_data : world_data)
    {
        if (obj_data.contains("tileImage"))
        {
            int index = 0;
            std::string data = obj_data["tileImage"][index++];
            // 기본이미지가 들어가있거나 이미지가 없으면 오브젝트를 생성하지 않는다
            if (data == "../Resource/tile/default.jpg") continue;
            if (data == "../Resource/tile\\default.jpg") continue;
            if (data == "") continue;

            int x = obj_data["tileImage"][index++] + _at.x;
            int y = obj_data["tileImage"][index++] + _at.y;

            std::wstring tmp;
            tmp.assign(data.begin(), data.end());

            GameObject* obj = m_pWorld->CreateGameObject<GameObject>();
            BitmapComponent* map = obj->AddComponent<BitmapComponent>("tileImage");
            map->SetBitmap(tmp);
            obj->GetRootComponent()->SetRelativeTranslation({ (float)x * TileSize + TileSize / 2,(float)y * TileSize + TileSize / 2 });
        }
        if (obj_data.contains("BG"))
        {
            int index = 0;
            string str = obj_data["BG"][index++];
            float x = obj_data["BG"][index++] + _at.x;
            float y = obj_data["BG"][index++] + _at.y ;

            wstring bitmapKey;
            bitmapKey.assign(str.begin(), str.end());
            
            GameObject* obj = m_pWorld->CreateGameObject<GameObject>();
            BitmapComponent* bitmap = obj->AddComponent<BitmapComponent>("BG");
            Vector2D size = bitmap->SetBitmap(bitmapKey);

            Vector2D pos = { x * TileSize + size.x / 2,y * TileSize + size.y / 2 };

            obj->GetRootComponent()->SetRelativeTranslation(pos);

        }
    }

}

void Load::DeleteTiles(GameObject*& _pTileObject)
{
    _pTileObject->Initialize();
    vector<GameObject*>& objects = m_pWorld->GetGameObjects();
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if (*it == _pTileObject)
        {
            objects.erase(it);
            delete _pTileObject;
            break;
        }
    }
}
