#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, 125.0f, -350.0f);
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<Player>("player");

	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,		//�΂˃J�����̏������s���J�������w�肷��B
		1000.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		5.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B

	);

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷�� //�����炭�ߕ��ʂƉ�����
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(50000.0f);

	return true;
}

void GameCamera::Update()
{


	//�J�����̍X�V
	//�����_���v�Z����
	Vector3 target = m_player->GetPosition();
	//target.x= m_player->m_position.x;
	////�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���
	target.y += 80.0f;

	/*Vector3 cameraPos;
	cameraPos = target;

	cameraPos.z -= 300.0f;

	g_camera3D->SetPosition(cameraPos);*/

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ��������
	float posX = g_pad[0]->GetRStickXF();
	float posY = g_pad[0]->GetRStickYF();
	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * posX);
	qRot.Apply(m_toCameraPos);
	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * posY);
	qRot.Apply(m_toCameraPos);
	//�J�����̉�]�̏�����`�F�b�N����
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.6f) {
		//�J�����������������
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.7f) {
		//�J������������������
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����
	Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷�邱��
	/*g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);*/

	//�o�l�J�����ɒ����_�Ǝ��_��ݒ肷��B
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(target);

	//�΂˃J�����̍X�V
	m_springCamera.Update();

	if (m_springCamera.GetCamera()->GetTargetToPositionLength() < 50.0f)
	{
		m_playerRenderFlag = false; //�v���C���[�𓧖��ɂ���
	}
	else
	{
		m_playerRenderFlag = true; //�v���C���[��s�����ɂ���
	}




	//�J�����̍X�V
	//g_camera3D->Update();

	//Vector3 distance = m_player->m_position - target;
	////�������߂���΃v���C���[�𓧖��ɂ���
	//if (distance.Length() < 100.0f) {
	//	//�v���C���[�𓧖��ɂ���
	//	m_player->SetAlpha(0.5f);
	//}
	//else {
	//	//�v���C���[��s�����ɂ���
	//	m_player->SetAlpha(1.0f);
	//}


}