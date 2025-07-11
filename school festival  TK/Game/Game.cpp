#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Star.h"
#include "MovingFloor.h"
#include "DownFloor.h"
#include "Score.h"
#include "Result.h"
#include "Title.h"
#include "Guide.h"
#include <algorithm>
#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "FreelyFloor.h"




namespace
{
	const Vector3 FONT_POSITION(500.f, 500.0f, 0.0f);
	const float FONT_SCALE(2.0f);

	//constは数値を変えたくない時に使うもの
}

Game::Game()
{
	

	
}

void Game::MakeStar(Vector3 pos){
	//Starクラスのオブジェクトを作る
	Star* star = NewGO<Star>(0, "Star");
	star->SetPosition(pos);
	star->m_firstPosition = pos;
	m_stars.push_back(star);
	
}

void Game::MovingObj(Vector3 pos)
{
	//動く床のオブジェクトを作る
	MovingFloor* movingFloor = NewGO<MovingFloor>(0, "movingFloor");
	movingFloor->m_position = pos;
	movingFloor->m_firstPosition = pos;
}

void Game::DownObj(Vector3 pos)
{
	//下に動く床のオブジェクトを作る
	DownFloor* downFloor = NewGO<DownFloor>(0, "downFloor");
	downFloor->m_position = pos;
	downFloor->m_firstPosition = pos;
}

void Game::FreelyObj(Vector3 pos)
{
	//自由に動く床のオブジェクトを作る
	FreelyFloor* freelyFloor = NewGO<FreelyFloor>(0, "freelyFloor");
	freelyFloor->SetPosition(pos);
	freelyFloor->m_firstPosition = pos;
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(gameCamera);
	DeleteGO(m_gameBGM);
	DeleteGO(backGround);
	DeleteGO(movingFloor);
	DeleteGO(downFloor);
	DeleteGO(score);
	DeleteGO(m_skyCube);
	auto totalStars = FindGOs<Star>("Star");//FindGOsは名前でオブジェクトを探す関数,()の中身は削除対象の中身と同じになるように
	for(auto Stars:totalStars)//for文で繰り返し削除、()の中に条件を入れる
	{
		DeleteGO(Stars);//DeleteGOはオブジェクトを削除する関数
	}
	auto totalMovingFloor = FindGOs<MovingFloor>("movingFloor");
	for (auto movingFloor : totalMovingFloor)
	{
		DeleteGO(movingFloor);
	}
	auto totalDownFloor = FindGOs<DownFloor>("downFloor");
	for(auto downFloor : totalDownFloor)
	{
		DeleteGO(downFloor);
	}
	auto totalFreelyFloor = FindGOs<FreelyFloor>("freelyFloor");
	for (auto freelyFloor : totalFreelyFloor)
	{
		DeleteGO(freelyFloor);
	}
}

bool Game::Start()
{


	

	//プレイヤーのオブジェクトを作る
	m_player = NewGO<Player>(1, "player");

	//ゲームカメラのオブジェクトを作る
	gameCamera = NewGO<GameCamera>(1, "gamecamera");

	//背景のオブジェクトを作る
	backGround = NewGO<BackGround>(1);

	//スコア
	score = NewGO<Score>(2, "score");

	//BGM
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/AS_149632_競争したくなる民族音楽.wav");
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(5);
	m_gameBGM->Play(true);


		MakeStar({ -90.0f,2800.0f,-500.0f });
		MakeStar({ -500.0f,350.0f,500.0f });
		MakeStar({ 100.0f,500.0f,890.0f });
		MakeStar({ 680.0f,1800.0f,-135.0f });
		MakeStar({ 1000.0f,4000.0f,400.0f });

		MovingObj({ 900.0f,3500.0f,500.0f });
		MovingObj({ 150.0f,1200.0f,0.0f });
		MovingObj({ 600.0f,2400.0f,-1200.0f });
		MovingObj({ 850.0f,4500.0f,1200.0f });
		MovingObj({ 2000.0f,4800.0f,0.0f });

		DownObj({ 1300.0f,1200.0f,600.0f });
		DownObj({ 1000.0f,1800.0f,-1500.0f });
		DownObj({ -100.0f,3900.0f,400.0f });
		DownObj({ 400.0f,3000.0f,-375.0f });
		
		FreelyObj({ 1400.0f,4000.0f,-400.0f });
		FreelyObj({ -300.0f,3000.0f,10.0f });
		FreelyObj({ 0.0f,4500.0f,1200.0f });
		FreelyObj({ -400.0f,2000.0f,100.0f });

	SkyCube* day = NewGO<SkyCube>(0);
	day->SetLuminance(0.2f);
	
	return true;
}

//更新処理
void Game::Update()
{	
	

	//MovingObj();
	
	//時間制限

		//m_timer -= g_gameTime->GetFrameDeltaTime();

	int sec = (int)m_timer;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	wchar_t text[256];
	//桁数の指定
	swprintf_s(text, 256, L"%02d", sec);
	//文字のセット
	m_timeFontRender.SetText(text);
	//文字の座標
	m_timeFontRender.SetPosition(FONT_POSITION);
	//文字の大きさ
	m_timeFontRender.SetScale(FONT_SCALE);
	//文字の色
	m_timeFontRender.SetColor(g_vec4Black);

		
	
	
	

		//m_timer -= g_gameTime->GetFrameDeltaTime();
		if (m_timer <= 1.0f) {

			

			result = NewGO<Result>(0, "result");
			result->m_climb_Point = int(m_player->GetPosition().y) / 100;
			result->m_star_Point = score->m_starCount;
			
			
			
			if (m_player->GetPosition().y <= 34.0f)
			{
				result->m_climb_Product = 0;
			}
			else
			{
				result->m_climb_Product += int(m_player->GetPosition().y) /2;
			}
			if (score->m_starCount <= 0)
			{
				result->m_star_Product = 0;
			}
			else
			{
				//星の数に応じてスコアを計算
				result->m_star_Product *= score->m_starCount;
				result->m_star_Product += result->m_climb_Product  / 10;
			}
			DeleteGO(this);

			
			return;
			
		}

		if (m_player->GetPosition().y >= 5500.0f) {

			result = NewGO<Result>(0, "result");
			result->m_climb_Point = int(m_player->GetPosition().y) / 100;
			result->m_star_Point = score->m_starCount;



			if (m_player->GetPosition().y <= 34.0f)
			{
				result->m_climb_Product = 0;
			}
			else
			{
				result->m_climb_Product += int(m_player->GetPosition().y) / 2;
			}
			if (score->m_starCount <= 0)
			{
				result->m_star_Product = 0;
			}
			else
			{
				//星の数に応じてスコアを計算
				result->m_star_Product *= score->m_starCount;
				result->m_star_Product += result->m_climb_Product / 10;
			}
			if (sec > 0) {
				result->m_timer_Product = sec/10;
				if (result->m_timer_Product <= 1) {
					result->m_timer_Product = 1;
				}
			}
			else
			{
				result->m_timer_Product = 0;
			}
			DeleteGO(this);


			return;
		}

		
		m_modelRender.Update();
}



void Game::Render(RenderContext& rc) 
{
	m_fontRender.Draw(rc);
	m_timeFontRender.Draw(rc);
}
