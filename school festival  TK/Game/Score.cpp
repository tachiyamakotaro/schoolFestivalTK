#include "stdafx.h"
#include "Score.h"
#include "Player.h"
#include "Game.h"
#include "Star.h"
#include "Result.h"

//#include <iostream>
//#include <string>
//#include <sstream>

using namespace std;

Score::Score()
{

}

Score::~Score()
{

}

bool Score::Start()
{
	player=FindGO<Player>("player");
	return true;
}

void Score::Update()
{
	//登った距離
	climbScore();

	//スターのスコア
	StarScore();

	/*result->star_Point = m_starCount;
	result->climb_Point = int(player->m_position.y);*/

	
}

void Score::StarScore()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"手に入れたスター: %d", m_starCount);
	m_fontRender_star.SetText(wcsbuf);
	
		m_fontRender_star.SetPosition({ -800.0f,330.0f,0.0f });
	
		//m_fontRender_star.SetPosition({ 0.0f,100.f,0.0f });
	m_fontRender_star.SetColor(g_vec4Yellow);
}

void Score::climbScore()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L" 登った距離: %d m",int(player->GetPosition().y)/100);
	m_fontRender_climb.SetText(wcsbuf);
	m_fontRender_climb.SetPosition({ -800.0f,250.0f,0.0f });
	m_fontRender_climb.SetColor(g_vec4Yellow);
}

void Score::Rank()
{

}

void Score::Render(RenderContext& rc)
{
	m_fontRender_star.Draw(rc);
	m_fontRender_climb.Draw(rc);
}