#pragma once
class Player;
class Score;
class Transform;

class Star :public IGameObject
{
public:
	Star();
	~Star();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();


	//メンバ変数
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
	///座標を設定
	/// </summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position);
};

