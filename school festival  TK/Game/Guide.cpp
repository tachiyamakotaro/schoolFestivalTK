#include "stdafx.h"
#include "Guide.h"
#include "Title.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"
#include <algorithm>
using namespace std;

Guide::Guide()
{

}

Guide::~Guide()
{

}

void Guide::setGuideState(int value) {
	if (value < MIN_STATE)value = MIN_STATE;
	if (value > MAX_STATE)value = MAX_STATE;
	m_guideState = value;
}

int Guide::getGuideState() const
{
	return 0;
}

bool Guide::Start()
{
	//画像の読み込み
	//m_spriteRender.Init("Assets/modelData/guide_morning.DDS",1920.0f,1080.0f);

	//BGM
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/AS_1118503_軽快でクールなチュートリアル向けBGM.wav");
	m_GuideBGM = NewGO<SoundSource>(0);
	m_GuideBGM->Init(3);
	m_GuideBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/AS_890910_決定／クリック／選択音（ピコンッ）.wav");
	//Guide g;						//上限と下限の設定
	//g.setGuideState(0);  //１に制限
	//cout << g.getGuideState() << endl; //出力１

	//g.setGuideState(2); //そのまま使える
	//cout << g.getGuideState() << endl; //出力2

	//g.setGuideState(100); //3に制限される
	//cout << g.getGuideState() << endl; //出力3
	return true;
}

void Guide::Update()
{
	if (g_pad[0]->IsTrigger(enButtonRight)) {
		m_GuideSE = NewGO<SoundSource>(0);
		m_GuideSE->Init(4);
		m_GuideSE->Play(false);
		m_guideState += 1;
		
	}
	if (g_pad[0]->IsTrigger(enButtonLeft)) {
		m_GuideSE = NewGO<SoundSource>(0);
		m_GuideSE->Init(4);
		m_GuideSE->Play(false);
		m_guideState -= 1;
		
	}
	
	

	switch (m_guideState) {
	case 1:
		
		m_spriteRender.Init("Assets/modelData/guide_morning.DDS",1920.0f,1080.0f);
		
		
		break;
	case 2:
		m_spriteRender.Init("Assets/modelData/guide_evening.DDS", 1920.0f, 1080.0f);
	
		break;
	case 3:
		m_spriteRender.Init("Assets/modelData/guide_night.DDS", 1920.0f, 1080.0f);
		
		if (g_pad[0]->IsTrigger(enButtonX)) {
			//効果音の再生
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(2);
			se->Play(false);

			NewGO<Title>(0);
			DeleteGO(this);
			DeleteGO(m_GuideBGM);
		}
		break;
	default:
		if (m_guideState < 1) {
			m_guideState = 1;
		}
		else if (m_guideState > 3) {
			m_guideState = 3;
		}
		break;
	}
	
}

void Guide::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}