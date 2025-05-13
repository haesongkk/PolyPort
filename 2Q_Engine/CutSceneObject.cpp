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
	// ¾Æ¹«Å°³ª ÀÔ·Â °¡´ÉÇÏ°Ô
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
			m_images.push_back(L"../Resource/image/cut_real/1. ¿ÀÇÁ´×/1. ¿ÀÇÁ´× 1.png");
			m_images.push_back(L"../Resource/image/cut_real/1. ¿ÀÇÁ´×/2. ¿ÀÇÁ´× 2.png");
			m_images.push_back(L"../Resource/image/cut_real/1. ¿ÀÇÁ´×/3. ¿ÀÇÁ´× 3.png");
			break;
		case CutScene::Insert1:
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/7. ÄÆ½Å 4.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/8. ÄÆ½Å 5.png");
			break;
		case CutScene::Insert2:
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/9. ÄÆ½Å 6.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/10. ÄÆ½Å 7.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/11. ÄÆ½Å 8.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/12. ÄÆ½Å 9.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/13. ÄÆ½Å 10.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/14. ÄÆ½Å 11.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/15. ÄÆ½Å 12.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/16. ÄÆ½Å 13.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/17. ÄÆ½Å 14.png");
			m_images.push_back(L"../Resource/image/cut_real/st2_1.png");
			m_images.push_back(L"../Resource/image/cut_real/st2_2.png");
			break;
		case CutScene::Insert3:
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/18. ÄÆ½Å 15.png");
			m_images.push_back(L"../Resource/image/cut_real/st3_1.png");
			m_images.push_back(L"../Resource/image/cut_real/st3_2.png");
			break;
		case CutScene::Ending:
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/19. ÄÆ½Å 16.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/20. ÄÆ½Å 17.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/21. ÄÆ½Å 18.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/22. ÄÆ½Å 19.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/23. ÄÆ½Å 20.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/24. ÄÆ½Å 21.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/25. ÄÆ½Å 22.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/26. ÄÆ½Å 23.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/27. ÄÆ½Å 24.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/28. ÄÆ½Å 25.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/29. ÄÆ½Å 26.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/30. ÄÆ½Å 27.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/31. ÄÆ½Å 28.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/32. ÄÆ½Å 29.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/33. ÄÆ½Å 30.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/34. ÄÆ½Å 31.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/35. ÄÆ½Å 32.png");
			m_images.push_back(L"../Resource/image/cut_real/2. ÄÆ½Å/36. ÄÆ½Å 33.png");
			break;
		case CutScene::EndingA:
			m_images.push_back(L"../Resource/image/cut_real/3. ¿£µù A/37.¿£µù A.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ¿£µù A/38. ¿£µù A ÁÜ¾Æ¿ô.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ¿£µù A/39. ¿£µù A ÆîÃÄÁø Ã¥.png");
			m_images.push_back(L"../Resource/image/cut_real/3. ¿£µù A/40. ¿£µù A ´ÝÈù Ã¥.png");
			break;
		case CutScene::EndingB:
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/41. ±úÁø ±¸½½.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/42. ¿©¿ì ±¸½½.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/43. ¿£µù B.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/44. ¿£µù B ÁÜ¾Æ¿ô.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/45. ¿£µù B ÆîÃÄÁø Ã¥.png");
			m_images.push_back(L"../Resource/image/cut_real/4. ¿£µù B/46. ¿£µù B ´ÝÈù Ã¥.png");
			break;
		
		case CutScene::Credit:
			m_images.push_back(L"../Resource/image/credit.png");
			break;
	}
	m_pImage = AddComponent<UIComponent>("ui");
	m_pImage->SetRelativeTranslation({ 960,540 });
	m_pImage->SetBitmap(m_images[m_index]);
}

