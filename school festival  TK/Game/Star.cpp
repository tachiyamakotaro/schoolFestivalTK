#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "Score.h"
#include "Transform.h"


Star::Star()
{
	m_transform = new Transform;

	//���̃��f����ǂݍ���
	m_modelRender.Init("Assets/modelData/star.tkm");

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/get.wav");

	player = FindGO<Player>("player");
	score = FindGO<Score>("score");
}

Star::~Star()
{
	delete m_transform;
}

void Star::Update()
{
	//�ړ�����
	Move();

	//��]����
	Rotation();

	//�G�`������̍X�V����
	m_modelRender.Update();

	Vector3 diff = player->GetPosition() - m_transform->m_localPosition;

	float difflength = diff.Length();

	if (diff.Length() <= 10.0f)
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);
		score->m_starCount += 1;
		DeleteGO(this);
	}
}

void Star::Move()
{
	if (m_moveState == 0)
	{
		m_transform->m_localPosition.y += 1.0f;
	}
	else if (m_moveState == 1)
	{
		m_transform->m_localPosition.y -= 1.0f;
	}

	if (m_transform->m_localPosition.y >= m_firstPosition.y + 30.0f)
	{
		m_moveState = 1;
	}
	else if (m_transform->m_localPosition.y <= m_firstPosition.y - 30.0f)
	{
		m_moveState = 0;
	}
	//�G�`������ɍ��W��������
	m_modelRender.SetPosition(m_transform->m_localPosition);
}

void Star::Rotation()
{
	m_transform->m_localRotation.AddRotationDegY(5.0f);

	m_modelRender.SetRotation(m_transform->m_localRotation);
}

void Star::Render(RenderContext& rc)
{
	//����`�悷��
	m_modelRender.Draw(rc);
}

///<summary>
	///���W��ݒ�
	/// </summary>
	/// <param name="position">���W�B</param>
void Star::SetPosition(const Vector3& position)
{
	m_transform->m_localPosition = position;
}