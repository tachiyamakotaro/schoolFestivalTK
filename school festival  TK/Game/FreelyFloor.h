#pragma once
class Player;
class Game;
class Transform;

class FreelyFloor :public IGameObject
{
public:
	FreelyFloor();
	~FreelyFloor() override;
	bool Start() override;
	void Update() override;
	void Render(RenderContext&rc) override;
	///<summary>
	///���W��ݒ�
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position);
	///<summary>
	///�ړ�����
	/// </summary>
	void Move();
	Vector3					m_firstPosition;
	ModelRender				m_modelRender;
	Player* m_player = nullptr;
	PhysicsStaticObject		m_physicsStaticObject;
	CollisionObject* m_collisionObject = nullptr;
	Game* m_game;
	enum enMovingFloorState
	{
		enMovingFloorState_MovingUp,
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingDown,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState		m_movingFloorState = enMovingFloorState_MovingUp;

	Transform* m_transform = nullptr;

};

