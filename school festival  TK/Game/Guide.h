#pragma once
#include"sound/SoundSource.h"

class Guide:public IGameObject
{
public:
	Guide();
	~Guide();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//�����o�ϐ�
	SoundSource* m_GuideBGM;
	SoundSource* m_GuideSE;

	SpriteRender m_spriteRender;
	int m_guideState =1;
	static constexpr int MIN_STATE = 1; //����Ɖ����̐ݒ�
	static constexpr int MAX_STATE = 3; //����Ɖ����̐ݒ�
	
	void setGuideState(int value); //����Ɖ����̐ݒ�
	int getGuideState() const; //����Ɖ����̐ݒ�
};

