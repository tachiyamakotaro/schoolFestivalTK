#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//�`��֐�
	//void Update();
	void Render(RenderContext& renderContext);
	PhysicsStaticObject physicsStaticObject;
	

	//���f�������_�[
	ModelRender m_modelRender;
};

