#include "pch.h"
#include "CutSceneObject.h"

#include "UIComponent.h"
#include "TextComponent.h"
#include "ButtonComponent.h"
#include "Input.h"
#include "Event.h"
#include "Load.h"
#include "World.h"
#include "Sound.h"

#define WordDelay 0.01f

CutSceneObject::CutSceneObject()
	:GameObject()
{
}

CutSceneObject::~CutSceneObject()
{
}

void CutSceneObject::Update(float dt)
{
  	__super::Update(dt);
	static float timer = 0;

	/*if (m_type == CutScene::Insert3)
	{
		timer += dt;
		if (timer < 1) return;
	}*/
	// �ƹ�Ű�� �Է� �����ϰ�
	for (int i = 0; i < (UINT)KEY::LAST; i++)
	{
 		if (Input::m_pInputInstance->GetKeyState((KEY)i) == KEY_STATE::TAP)
		{
			if ((KEY)i == KEY::LEFT)
			{
				if (m_index != 0) m_index--;
			}
			else
			{
				if (++m_index == m_images.size())
				{
					Event::DeleteWorld();
					Event::DeleteObject(this);
					
					if (m_type == CutScene::EndingA || m_type == CutScene::EndingB)
					{
						m_pWorld->LoadScene(LOADSCENE::Credit);
						return;
					}
					m_pWorld->LoadNextScene();
					timer = 0;
					return;
				}
				if (m_type == CutScene::Insert1 && m_index == 4)
				{
					Sound::Stop(BGM);
					Sound::Play(CHANNEL::BGM, "../Resource/sound/(loop)3.legend_insert1_insert.wav");
				}
				if (m_type == CutScene::Insert2 && m_index == 3)
				{
					Sound::Play(SFX, "../Resource/sound/break.wav");
				}
				if (m_type == CutScene::Insert2 && m_index == 6)
				{
					Sound::Stop(BGM);
					Sound::Play(CHANNEL::BGM, "../Resource/sound/(loop)5.toyou_insert2_insert.mp3");
				}
				if (m_type == CutScene::Ending && m_index == 13)
				{
					Sound::Stop(BGM);
					Sound::Play(CHANNEL::BGM, "../Resource/sound/(loop)8.two_ending_insert.mp3");
				}
				
			}
			
			m_pImage->SetBitmap(m_images[m_index]);
			break;
		}
	}
}

void CutSceneObject::SetCutSceneType(CutScene _cutScene)
{
	m_type = _cutScene;
	switch (_cutScene)
	{
		case CutScene::Opening:
			m_images.push_back(L"../Resource/image/cut_real/1. ������/1. ������ 1.png");
			m_images.push_back(L"../Resource/image/cut_real/1. ������/2. ������ 2.png");
			m_images.push_back(L"../Resource/image/cut_real/1. ������/3. ������ 3.png");
			break;
		case CutScene::Insert1:
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/7. �ƽ� 4.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/8. �ƽ� 5.png");
			break;
		case CutScene::Insert2:
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/9. �ƽ� 6.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/10. �ƽ� 7.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/11. �ƽ� 8.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/12. �ƽ� 9.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/13. �ƽ� 10.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/14. �ƽ� 11.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/15. �ƽ� 12.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/16. �ƽ� 13.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/17. �ƽ� 14.png");
			m_images.push_back(L"../Resource/image/cut_real/st2_1.png");
			m_images.push_back(L"../Resource/image/cut_real/st2_2.png");
			break;
		case CutScene::Insert3:
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/18. �ƽ� 15.png");
			m_images.push_back(L"../Resource/image/cut_real/st3_1.png");
			m_images.push_back(L"../Resource/image/cut_real/st3_2.png");
			break;
		case CutScene::Ending:
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/19. �ƽ� 16.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/20. �ƽ� 17.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/21. �ƽ� 18.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/22. �ƽ� 19.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/23. �ƽ� 20.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/24. �ƽ� 21.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/25. �ƽ� 22.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/26. �ƽ� 23.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/27. �ƽ� 24.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/28. �ƽ� 25.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/29. �ƽ� 26.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/30. �ƽ� 27.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/31. �ƽ� 28.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/32. �ƽ� 29.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/33. �ƽ� 30.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/34. �ƽ� 31.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/35. �ƽ� 32.png");
			m_images.push_back(L"../Resource/image/cut_real/2. �ƽ�/36. �ƽ� 33.png");
			break;
		case CutScene::EndingA:
			m_images.push_back(L"../Resource/image/cut_real/3. ���� A/37.���� A.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ���� A/38. ���� A �ܾƿ�.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ���� A/39. ���� A ������ å.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ���� A/40. ���� A ���� å.png");
			break;
		case CutScene::EndingB:
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/41. ���� ����.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/42. ���� ����.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/43. ���� B.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/44. ���� B �ܾƿ�.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/45. ���� B ������ å.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ���� B/46. ���� B ���� å.png");
			break;
		
		case CutScene::Credit:
			m_images.push_back(L"../Resource/image/credit.png");
			break;
	}
	m_pImage = AddComponent<UIComponent>("ui");
	m_pImage->SetRelativeTranslation({ 960,540 });
	m_pImage->SetBitmap(m_images[m_index]);
}

