#pragma once

class Player;
class Game;

class MovingFloor : public IGameObject
{
public:
	MovingFloor();
	~MovingFloor();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	///<summary>
	///座標を設定
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	///<summary>
	///移動処理
	/// </summary>
	void Move();
	Vector3					m_position;
	Vector3					m_firstPosition;
	ModelRender				m_modelRender;
	Player*					m_player = nullptr;
	PhysicsStaticObject		m_physicsStaticObject;
	CollisionObject*		m_collisionObject = nullptr;
	Game*					m_game;
	enum enMovingFloorState
	{
		enMovingFloorState_MovingUp,
		enMovingFloorState_MovingDown
	};
	enMovingFloorState		m_movingFloorState = enMovingFloorState_MovingUp;
};

