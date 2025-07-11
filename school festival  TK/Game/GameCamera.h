#pragma once
#include "camera/SpringCamera.h"

class Player;
//�Q�[�����̃J�����𐧌䂷��
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	//�����o�ϐ�

	Player* m_player;
	Vector3 m_toCameraPos;
	SpringCamera m_springCamera;   //�΂˃J����
	
	bool m_playerRenderFlag; //�v���C���[�̕`��t���O
};

