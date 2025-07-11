#pragma once
class Player;
class Score;
class Transform;

class Star :public IGameObject
{
public:
	Star();
	~Star();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//��]����
	void Rotation();


	//�����o�ϐ�
	ModelRender m_modelRender;
	int m_moveState = 0;
	Vector3 m_firstPosition;
	Player* player;
	Score* score;
	Transform* m_transform = nullptr;

	Transform* GetTransform()
	{
		return m_transform;
	}

	///<summary>
	///���W��ݒ�
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position);
};

