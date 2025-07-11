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
	//ƒƒ“ƒo•Ï”
	SoundSource* m_GuideBGM;
	SoundSource* m_GuideSE;

	SpriteRender m_spriteRender;
	int m_guideState =1;
	static constexpr int MIN_STATE = 1; //ãŒÀ‚Æ‰ºŒÀ‚Ìİ’è
	static constexpr int MAX_STATE = 3; //ãŒÀ‚Æ‰ºŒÀ‚Ìİ’è
	
	void setGuideState(int value); //ãŒÀ‚Æ‰ºŒÀ‚Ìİ’è
	int getGuideState() const; //ãŒÀ‚Æ‰ºŒÀ‚Ìİ’è
};

