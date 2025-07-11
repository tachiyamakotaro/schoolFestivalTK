#include "stdafx.h"
#include "Player.h"
#include "Score.h"
#include "GameCamera.h"

#include<iostream>

#include"sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Transform.h"
#include "FreelyFloor.h"

Player::Player()
{
	//モデルを初期化する
	
	m_transform = new Transform;
	
}

Player::~Player()
{
	delete m_transform;
}
bool Player::Start()
{
	//アニメーションクリップをロードする
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	//animationClips[enAnimationCilp_Run].SetLoopFlag(false);

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/AS_69491_ぽいっ（ジャンプ、かわいい、低めの音）.wav");

	//ユニティちゃんのモデルを読み込む
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips,
		enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する
	m_characterController.Init(20.0f, 65.0f, m_transform->m_localPosition);

	m_initialPosition =Vector3(-300.0f,0.0f,-500.0f);

	m_gameCamera=FindGO<GameCamera>("gamecamera");

	return true;
}



void Player::Update()
{
	//移動処理
	Move();

	//回転処理
	Rotation();

	
	

	if (m_transform->m_localPosition.y <= -0.2f) {
		m_transform->m_localPosition = m_initialPosition;
		m_moveSpeed = Vector3::Zero;
		m_transform->m_localRotation.SetRotationDegY(0.0f);
		m_characterController.SetPosition(m_transform->m_localPosition);
		m_modelRender.SetPosition(m_transform->m_localPosition);
		
	}
	
	
	m_transform->UpdateTransform();
	m_modelRender.SetTRS(m_transform->m_localPosition, m_transform->m_localRotation, m_transform->m_localScale);
	m_modelRender.Update();
	
}


void Player::Move()
{
	//xzの移動速度を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左クリックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算
	right *= stickL.x * 700.0f;
	forward *= stickL.y * 700.0f;

	//移動速度に上記で計算したベクトルを加算する
	m_moveSpeed += right + forward;

	////移動速度にスティックの入力量を加算する
	//m_moveSpeed.x *= stickL.x * 10.0f;
	//m_moveSpeed.z *= stickL.y * 10.0f;

	//地面に着いていたら
	m_moveSpeed.y -= 7.0f;
	if (m_playerState == 0) {
		if (m_characterController.IsOnGround() == true)
		{

			if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {

				m_modelRender.PlayAnimation(enAnimationClip_Run);
			}
			else {
				m_modelRender.PlayAnimation(enAnimationClip_Idle);
			}

			//重力を無くす
			//m_moveSpeed.y = 0.0f;
			//Aボタンが押されたら
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				m_moveSpeed.y = 500.0f;
				m_playerState = 1;
				m_modelRender.PlayAnimation(enAnimationClip_Jump);
				jumpSE = NewGO<SoundSource>(0);
				jumpSE->Init(6);
				jumpSE->Play(false);
			}
		}

		//地面に付いていなかったら
		else
		{
			//落下中の処理
			m_playerState = 1;

		}
	}

	if (m_playerState == 1) {
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_moveSpeed.y = 500.0f;
			m_modelRender .PlayAnimation(enAnimationClip_Idle);
			m_modelRender.PlayAnimation(enAnimationClip_Jump);
			m_playerState = 2;
			jumpSE = NewGO<SoundSource>(0);
			jumpSE->Init(6);
			jumpSE->Play(false);
		}
		if (m_characterController.IsOnGround() == true) {
			m_playerState = 0;
		}
	}
	if (m_playerState == 2) {
		if (m_characterController.IsOnGround() == true) {
			m_playerState = 0;
		}
	}
	
	
	

	//キャラクターコントローラーを使って座標を移動させる
	m_transform->m_localPosition = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	

	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_transform->m_localPosition);

	
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら）
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える
		m_transform->m_localRotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える
		m_modelRender.SetRotation(m_transform->m_localRotation);
	}
}

const Vector3& Player::GetPosition()
{
	return m_transform->m_localPosition;
}

void Player::Render(RenderContext& renderContext)
{
	if (m_gameCamera->m_playerRenderFlag == true) {
		//モデルを表示する
		m_modelRender.Draw(renderContext);
	}

	if (m_gameCamera->m_playerRenderFlag == false) {
		//モデルを表示しない
	}
}

void Player::ReleaseParent()
{
	m_transform->Release();
}