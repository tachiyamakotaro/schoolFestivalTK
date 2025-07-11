#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//•`‰æŠÖ”
	//void Update();
	void Render(RenderContext& renderContext);
	PhysicsStaticObject physicsStaticObject;
	

	//ƒ‚ƒfƒ‹ƒŒƒ“ƒ_[
	ModelRender m_modelRender;
};

