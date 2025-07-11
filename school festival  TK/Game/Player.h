#pragma once
#include "sound/SoundSource.h"

class Score;
class GameCamera;
class Transform;

class Player:public IGameObject
{
public:
	Player();   //�R���X�g���N�^�@�@NewGO�������Ɏg����Start���g�����ق�������
	~Player();  //�`�̓f�X�g���N�^�@DeleteGO���������ɌĂ΂��
	bool Start() override;
	void Update();
	//�`�揈��
	void Render(RenderContext& renderContext);
	//�ړ�����
	void Move();
	//��]����
	void Rotation();

		
	const Vector3& GetPosition();
	///<summary>
	///	�ړ����x�����Z
	/// </summary>
	/// <param name="addMoveSpeed">���Z����ړ����x</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	///<summary>
	///	�L�����N�^�[�R���g���[���[
	/// </summary>
	/// <returns>�L�����N�^�[�R���g���[���[</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


	//�������烁���o�ϐ�
	ModelRender m_modelRender;
	Vector3 m_initialPosition;
	enum EnAnimationClip {//�A�j���[�V����
		enAnimationClip_Idle,
		//enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Vector3 m_moveSpeed;
	int m_playerState = 0; 
	

	Score* score;
	SoundSource* jumpSE;
	GameCamera* m_gameCamera;
	Transform* m_transform=nullptr;
	
	float m_alpha = 1.0f; //�����x

	Transform* GetTransform()
	{
		return m_transform;
	}

	void ReleaseParent();
};

