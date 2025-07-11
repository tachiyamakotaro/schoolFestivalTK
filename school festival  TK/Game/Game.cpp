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

	//const�͐��l��ς������Ȃ����Ɏg������
}

Game::Game()
{
	

	
}

void Game::MakeStar(Vector3 pos){
	//Star�N���X�̃I�u�W�F�N�g�����
	Star* star = NewGO<Star>(0, "Star");
	star->SetPosition(pos);
	star->m_firstPosition = pos;
	m_stars.push_back(star);
	
}

void Game::MovingObj(Vector3 pos)
{
	//�������̃I�u�W�F�N�g�����
	MovingFloor* movingFloor = NewGO<MovingFloor>(0, "movingFloor");
	movingFloor->m_position = pos;
	movingFloor->m_firstPosition = pos;
}

void Game::DownObj(Vector3 pos)
{
	//���ɓ������̃I�u�W�F�N�g�����
	DownFloor* downFloor = NewGO<DownFloor>(0, "downFloor");
	downFloor->m_position = pos;
	downFloor->m_firstPosition = pos;
}

void Game::FreelyObj(Vector3 pos)
{
	//���R�ɓ������̃I�u�W�F�N�g�����
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
	auto totalStars = FindGOs<Star>("Star");//FindGOs�͖��O�ŃI�u�W�F�N�g��T���֐�,()�̒��g�͍폜�Ώۂ̒��g�Ɠ����ɂȂ�悤��
	for(auto Stars:totalStars)//for���ŌJ��Ԃ��폜�A()�̒��ɏ���������
	{
		DeleteGO(Stars);//DeleteGO�̓I�u�W�F�N�g���폜����֐�
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


	

	//�v���C���[�̃I�u�W�F�N�g�����
	m_player = NewGO<Player>(1, "player");

	//�Q�[���J�����̃I�u�W�F�N�g�����
	gameCamera = NewGO<GameCamera>(1, "gamecamera");

	//�w�i�̃I�u�W�F�N�g�����
	backGround = NewGO<BackGround>(1);

	//�X�R�A
	score = NewGO<Score>(2, "score");

	//BGM
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/AS_149632_�����������Ȃ閯�����y.wav");
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

//�X�V����
void Game::Update()
{	
	

	//MovingObj();
	
	//���Ԑ���

		//m_timer -= g_gameTime->GetFrameDeltaTime();

	int sec = (int)m_timer;
	m_timer -= g_gameTime->GetFrameDeltaTime();

	wchar_t text[256];
	//�����̎w��
	swprintf_s(text, 256, L"%02d", sec);
	//�����̃Z�b�g
	m_timeFontRender.SetText(text);
	//�����̍��W
	m_timeFontRender.SetPosition(FONT_POSITION);
	//�����̑傫��
	m_timeFontRender.SetScale(FONT_SCALE);
	//�����̐F
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
				//���̐��ɉ����ăX�R�A���v�Z
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
				//���̐��ɉ����ăX�R�A���v�Z
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
