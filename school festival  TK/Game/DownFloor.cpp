#include "stdafx.h"
#include "DownFloor.h"

#include "Player.h"

namespace
{
	Vector3 SCALE = Vector3(1.0f, 1.0, 1.0f);
	float SPEED = 200.0f;
	float LIMITED = 300.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 30.0f, 0.0f);
	Vector3 COLLISION_SIZE = Vector3(100.0f, 10.0f, 150.0f);
}

DownFloor::DownFloor()
{

}

DownFloor::~DownFloor()
{

}

bool DownFloor::Start()
{
	m_modelRender.Init("Assets/modelData/stage/sky_cloud01.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//コリジョンオブジェクトを
	//動く床の上に設置する(キャラクターが上に乗ったら反応するようにしたいため)
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition = m_position;

	m_player = FindGO<Player>("player");
	return true;
}

void DownFloor::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	Move();

	m_modelRender.Update();

	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

void DownFloor::Move()
{
	Vector3 moveSpeed = Vector3::Zero;

	if (m_movingFloorState == enDownFloorState_MovingDown)
	{
		moveSpeed.y = -SPEED;
	}
	else if (m_movingFloorState == enDownFloorState_MovingUp)
	{
		moveSpeed.y = SPEED;
	}

	m_position -= moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_movingFloorState == enDownFloorState_MovingDown)
	{
		if (m_firstPosition.y + LIMITED <= m_position.y)
		{
			m_movingFloorState = enDownFloorState_MovingUp;
		}
	}
	else if (m_movingFloorState == enDownFloorState_MovingUp)
	{
		if (m_firstPosition.y - LIMITED >= m_position.y)
		{
			m_movingFloorState = enDownFloorState_MovingDown;
		}
	}

	m_modelRender.SetPosition(m_position);

	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが
	//衝突したら(キャラクターが動く床の上に乗ったら)

}

void DownFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}