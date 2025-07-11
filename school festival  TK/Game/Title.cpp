#include "stdafx.h"
#include "Title.h"
#include "Score.h"
#include "Game.h"
#include "Guide.h"
#include "Result.h"

Title::Title()
{

}

Title::~Title()
{
	
}

bool Title::Start()
{
	//タイトル画面の読み込み処理
	m_spriteRender.Init("Assets/modelData/sky_Title02.DDS",1920.0f,1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/AS_837826_まるで空を飛んでいるようなピアノ曲.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(0);
	m_titleBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/AS_149609_ゲームスタート音.wav");
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//効果音の再生
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);

		NewGO<Game>(0, "game");
		//NewGO<Result>(0, "result");
		DeleteGO(this);
		DeleteGO(m_titleBGM);
	}

	if (g_pad[0]->IsTrigger(enButtonX))
	{
		//効果音の再生
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);

		NewGO<Guide>(0, "guide");
		DeleteGO(this);
		DeleteGO(m_titleBGM);
	}
}

void Title::Render(RenderContext& rc)
{
	//画像を描画する
	m_spriteRender.Draw(rc);
}
