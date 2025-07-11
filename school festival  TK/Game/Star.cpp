#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "Score.h"
#include "Transform.h"


Star::Star()
{
	m_transform = new Transform;

	//☆のモデルを読み込む
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
	//移動処理
	Move();

	//回転処理
	Rotation();

	//絵描きさんの更新処理
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
	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_transform->m_localPosition);
}

void Star::Rotation()
{
	m_transform->m_localRotation.AddRotationDegY(5.0f);

	m_modelRender.SetRotation(m_transform->m_localRotation);
}

void Star::Render(RenderContext& rc)
{
	//☆を描画する
	m_modelRender.Draw(rc);
}

///<summary>
	///座標を設定
	/// </summary>
	/// <param name="position">座標。</param>
void Star::SetPosition(const Vector3& position)
{
	m_transform->m_localPosition = position;
}