#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//描画関数
	//void Update();
	void Render(RenderContext& renderContext);
	PhysicsStaticObject physicsStaticObject;
	

	//モデルレンダー
	ModelRender m_modelRender;
};

