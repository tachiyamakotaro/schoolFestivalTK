#include "stdafx.h"
#include "FreelyFloor.h"

#include"Player.h"
#include "Game.h"
#include "Transform.h"

namespace
{
	const Vector3 SCALE = Vector3(1.0f, 1.0, 1.0f);
	float SPEED = 300.0f;
	float LIMITED = 500.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 30.0f, 0.0f);
	Vector3 COLLISION_SIZE = Vector3(100.0f, 10.0f, 150.0f);
	Quaternion m_rotation;

	float ROTATESPEED = 2.0f;
}

FreelyFloor::FreelyFloor()
{
	m_transform = new Transform;
}

FreelyFloor::~FreelyFloor()
{
	delete m_transform;
}

bool FreelyFloor::Start()
{
	m_modelRender.Init("Assets/modelData/stage/sky_Tiles01.tkm");
	m_modelRender.SetScale(SCALE);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//コリジョンオブジェクトを
	//動く床の上に設置する(キャラクターが上に乗ったら反応するようにしたいため)
	m_collisionObject->CreateBox(
		m_transform->m_localPosition + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition = m_transform->m_localPosition;

	m_player = FindGO<Player>("player");
	return true;
}

void FreelyFloor::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	Move();

	m_transform->UpdateTransform();
	m_modelRender.SetTRS(m_transform->m_localPosition, m_transform->m_localRotation, m_transform->m_localScale);
	m_modelRender.Update();

	m_physicsStaticObject.SetPosition(m_transform->m_localPosition);
	m_collisionObject->SetPosition(m_transform->m_localPosition + COLLISION_HEIGHT);



}

void FreelyFloor::Move()
{

	Vector3 moveSpeed = Vector3::Zero;

	if (m_movingFloorState == enMovingFloorState_MovingUp)
	{
		moveSpeed.y = -SPEED;

	}
	else if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.x = -SPEED;

	}
	else if (m_movingFloorState == enMovingFloorState_MovingDown)
	{
		moveSpeed.y = SPEED;

	}
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.x = SPEED;

	}


	m_transform->m_localPosition += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_movingFloorState == enMovingFloorState_MovingUp)
	{
		if (m_firstPosition.y - LIMITED >= m_transform->m_localPosition.y)
		{
			m_movingFloorState = enMovingFloorState_MovingRight;
		}
	}
	else if (m_movingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.x - LIMITED >= m_transform->m_localPosition.x)
		{
			m_movingFloorState = enMovingFloorState_MovingDown;
		}
	}
	else if (m_movingFloorState == enMovingFloorState_MovingDown)
	{
		if (m_firstPosition.y + LIMITED <= m_transform->m_localPosition.y)
		{
			m_movingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_movingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.x + LIMITED <= m_transform->m_localPosition.x)
		{
			m_movingFloorState = enMovingFloorState_MovingUp;
		}
	}

	m_transform->m_position = m_transform->m_localPosition;

	m_modelRender.SetPosition(m_transform->m_localPosition);

	// キャラクターが動く床に乗ったら
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_player->GetTransform()->SetParent(m_transform);

		//動く床の移動速度をキャラクターの移動速度に加算。
		//m_player->AddMoveSpeed(moveSpeed);
	}
	else
	{
		m_player->ReleaseParent();
	}
}

void FreelyFloor::SetPosition(const Vector3& position)
{
	m_transform->m_localPosition = position;
}

void FreelyFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}