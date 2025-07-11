#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/modelData/stage/skyBlock01.tkm");

	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	Quaternion m_rot;
	m_rot.SetRotationDegX(90.0f);
	m_modelRender.SetRotation(m_rot);


}

BackGround::~BackGround()
{

}

//void BackGround::Update()
//{
//	m_modelRender.Update();
//}

void BackGround::Render(RenderContext& rc)
{
	//ƒ‚ƒfƒ‹‚ð•`‰æ‚·‚é
	m_modelRender.Draw(rc);
}