#include "stdafx.h"
#include "Result.h"
#include "Score.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Title.h"
#include "Game.h"
#include "MovingFloor.h"
#include "downFloor.h"
#include "Player.h"


namespace
{
	const float FONT_SCALE(2.0f);
	const float TOTAL_FONT_SCALE(4.0f);
}
//リザルト画面
Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	
		m_spriteRender.Init("Assets/modelData/result_01.DDS", 1920.0f, 1080.0f);
		g_soundEngine->ResistWaveFileBank(7, "Assets/sound/AS_804975_リコーダーとアコーディオンが奏でる軽快な.wav");
		g_soundEngine->ResistWaveFileBank(8, "Assets/sound/AS_968474_大量のお金がジャラジャラ降ってくる音.wav");
		m_resultBGM = NewGO<SoundSource>(0, "ResultBGM");
		m_resultBGM->Init(7);
		m_resultBGM->Play(true);
		m_resultSE = NewGO<SoundSource>(0);
		m_resultSE->Init(8);
		m_resultSE->Play(true);

		m_fontRender_skip.SetText(L"Xボタンでスキップ");
		m_fontRender_skip.SetScale(1.0f);
		m_fontRender_skip.SetPosition({ 480.0f, 350.0f, 0.0f });
		m_fontRender_skip.SetColor(g_vec4Yellow);

	return true;
}

void Result::Update()
{
	DrawResult();

	ClimbResult();

	StarResult();

	TotalResult();
	if (m_drawState == 3) {
		if (g_pad[0]->IsTrigger(enButtonA))
		{


			NewGO<Title>(0);
			DeleteGO(this);
			DeleteGO(m_resultBGM);

		}
	}
}

void Result::ClimbResult()
{	
	wchar_t Climb_Point[256];
	//桁数の指定
	swprintf_s(Climb_Point, 256, L"%d", m_climb_Point);
	m_fontRender_climb_Point.SetText(Climb_Point);
	m_fontRender_climb_Point.SetScale(FONT_SCALE);
	m_fontRender_climb_Point.SetPosition({ -200.0f, 250.0f, 0.0f });
	m_fontRender_climb_Point.SetColor(g_vec4Yellow);

	wchar_t Climb_Product[256];
	//桁数の指定
	//掛け算された登った距離
	swprintf_s(Climb_Product, 256, L"%d", m_climb_Product_Draw);
	m_fontRender_climb_Product.SetText(Climb_Product);
	m_fontRender_climb_Product.SetScale(FONT_SCALE);
	m_fontRender_climb_Product.SetPosition({ 200.0f, 250.0f, 0.0f });
	m_fontRender_climb_Product.SetColor(g_vec4Yellow);
}

void Result::StarResult()
{
	wchar_t Star_Point[256];
	swprintf_s(Star_Point, 256, L"%d", m_star_Point);
	m_fontRender_star_Point.SetText(Star_Point);
	m_fontRender_star_Point.SetScale(FONT_SCALE);
	m_fontRender_star_Point.SetPosition({ -200.0f, 90.0f, 0.0f });
	m_fontRender_star_Point.SetColor(g_vec4Yellow);

	wchar_t Star_Product[256];
	//掛け算された星の数
	swprintf_s(Star_Product, 256, L"%d", m_star_Product_Draw);
	m_fontRender_star_Product.SetText(Star_Product);
	m_fontRender_star_Product.SetScale(FONT_SCALE);
	m_fontRender_star_Product.SetPosition({ 200.0f, 90.0f, 0.0f });
	m_fontRender_star_Product.SetColor(g_vec4Yellow);
}

void Result::TotalResult()
{
		//合計のポイントを計算
	
	wchar_t Total_Point[256];
	swprintf_s(Total_Point, 256, L"%d", m_total_Point_Draw);
	m_fontRender_total_Point.SetText(Total_Point);
	m_fontRender_total_Point.SetScale(TOTAL_FONT_SCALE);
	m_fontRender_total_Point.SetPosition({ -250.0f, -200.0f, 0.0f });
	m_fontRender_total_Point.SetColor(g_vec4Yellow);
}

void Result::DrawResult()
{
	m_drawTimer -= g_gameTime->GetFrameDeltaTime();
	if( m_drawTimer <= 0.0f )
	{
		//リザルトの表示を行う
		//登った距離の表示
		if (m_drawState == 0) {
			if (m_climb_Product_Draw < m_climb_Product) {
				m_climb_Product_Draw++;
				m_drawTimer = 0.00000000000000000001f;
			}
			if (m_climb_Product_Draw == m_climb_Product) {
				m_drawState = 1;
			}
		}
		//星の数の表示
	    if (m_drawState == 1) {
			if (m_star_Product_Draw < m_star_Product) {
				m_star_Product_Draw++;
				m_drawTimer = 0.00000000000000000001f;
			}
			if (m_star_Product_Draw == m_star_Product) {
				m_drawState = 2;
			}
		}
		//合計ポイントの表示
		if (m_drawState == 2) {
			m_total_Point = m_climb_Product + m_star_Product;
			if (m_timer_Product >1) {
				m_total_Point *= m_timer_Product;
				m_fontRender_timer.SetText(L"のこりじかんボーナス:");
				m_fontRender_timer.SetScale(1.0f);
				m_fontRender_timer.SetPosition({-100.0f, -100.0f, 0.0f });
				m_fontRender_timer.SetColor(g_vec4Yellow);
			}
			if (m_total_Point_Draw < m_total_Point) {

				m_total_Point_Draw++;
				m_drawTimer = 0.00000000000000000001f;
			}
			if (m_total_Point_Draw == m_total_Point) {
				m_drawState = 3;
			}
		}
		
		if(m_drawState==0 or m_drawState==1 or m_drawState==2 )
		{
			
			if(g_pad[0]->IsTrigger(enButtonX))
			{
				m_climb_Product_Draw = m_climb_Product;
				m_star_Product_Draw = m_star_Product;
				m_total_Point_Draw = m_total_Point;
			}
		}
		if(m_drawState==3)
		{
			DeleteGO(m_resultSE);
		}
		
	}
	
}

void Result::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender_star_Point.Draw(rc);
	m_fontRender_climb_Point.Draw(rc);
	m_fontRender_climb_Product.Draw(rc);
	m_fontRender_star_Product.Draw(rc);
	m_fontRender_total_Point.Draw(rc);
	m_fontRender_skip.Draw(rc);
	m_fontRender_timer.Draw(rc);
}


