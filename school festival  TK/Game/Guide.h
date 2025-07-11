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
	//メンバ変数
	SoundSource* m_GuideBGM;
	SoundSource* m_GuideSE;

	SpriteRender m_spriteRender;
	int m_guideState =1;
	static constexpr int MIN_STATE = 1; //上限と下限の設定
	static constexpr int MAX_STATE = 3; //上限と下限の設定
	
	void setGuideState(int value); //上限と下限の設定
	int getGuideState() const; //上限と下限の設定
};

