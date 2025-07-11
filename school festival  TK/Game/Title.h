#pragma once
#include "sound/SoundSource.h"

//class Result;

class Title :public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Render(RenderContext& rc);
	void Update();

	//�����o�ϐ�
	SpriteRender  m_spriteRender;
	SoundSource* m_titleBGM;
	//Result* score;

};

