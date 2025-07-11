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
	//���f��������������
	
	m_transform = new Transform;
	
}

Player::~Player()
{
	delete m_transform;
}
bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	//animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	//animationClips[enAnimationCilp_Run].SetLoopFlag(false);

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/AS_69491_�ۂ����i�W�����v�A���킢���A��߂̉��j.wav");

	//���j�e�B�����̃��f����ǂݍ���
	m_modelRender.Init("Assets/modelData/unityChan.tkm", animationClips,
		enAnimationClip_Num, enModelUpAxisY);

	//�L�����R��������������
	m_characterController.Init(20.0f, 65.0f, m_transform->m_localPosition);

	m_initialPosition =Vector3(-300.0f,0.0f,-500.0f);

	m_gameCamera=FindGO<GameCamera>("gamecamera");

	return true;
}



void Player::Update()
{
	//�ړ�����
	Move();

	//��]����
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
	//xz�̈ړ����x��0.0f�ɂ���
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���N���b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z
	right *= stickL.x * 700.0f;
	forward *= stickL.y * 700.0f;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z����
	m_moveSpeed += right + forward;

	////�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����
	//m_moveSpeed.x *= stickL.x * 10.0f;
	//m_moveSpeed.z *= stickL.y * 10.0f;

	//�n�ʂɒ����Ă�����
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

			//�d�͂𖳂���
			//m_moveSpeed.y = 0.0f;
			//A�{�^���������ꂽ��
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

		//�n�ʂɕt���Ă��Ȃ�������
		else
		{
			//�������̏���
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
	
	
	

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������
	m_transform->m_localPosition = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	

	//�G�`������ɍ��W��������
	m_modelRender.SetPosition(m_transform->m_localPosition);

	
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������j
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���
		m_transform->m_localRotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������
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
		//���f����\������
		m_modelRender.Draw(renderContext);
	}

	if (m_gameCamera->m_playerRenderFlag == false) {
		//���f����\�����Ȃ�
	}
}

void Player::ReleaseParent()
{
	m_transform->Release();
}