#pragma once

class Player;

class DownFloor :public IGameObject
{
public:
	DownFloor();
	~DownFloor();
	bool Start() override;
	void Update()override;
	void Render(RenderContext& rc) override;
	///<summary>
	///ç¿ïWÇê›íË
	///</summary>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	///<summary>
	///à⁄ìÆèàóù
	///</summary>
	void Move();
	Vector3					m_position;
	Vector3					m_firstPosition;
	ModelRender				m_modelRender;
	Player* m_player = nullptr;
	PhysicsStaticObject		m_physicsStaticObject;
	CollisionObject* m_collisionObject = nullptr;
	enum enDownFloorState
	{
		enDownFloorState_MovingDown,
		enDownFloorState_MovingUp
	};
	enDownFloorState		m_movingFloorState = enDownFloorState_MovingDown;
};

