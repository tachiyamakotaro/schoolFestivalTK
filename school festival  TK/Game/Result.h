#pragma once
#include"sound/SoundSource.h"

class Title;
class Score;
class Player;
class Star;
class Game;

class Result:public IGameObject
{
public:
	Result();
	~Result();

	bool Start();
	void Render(RenderContext& rc);
	void Update();
	void ClimbResult();
	void StarResult();
	void TotalResult();
	void DrawResult();
	
	//void Point();

	//メンバ変数
	SpriteRender m_spriteRender;
	 
	int m_star_Point;
	int m_climb_Point;
	int m_climb_Product=0;
	int m_star_Product=200;
	float m_total_Point = 0;
	//float m_timer_Point = 0;
	float m_timer_Product = 0;

	int m_climb_Product_Draw = 0;
	int m_star_Product_Draw = 0;
	int m_total_Point_Draw = 0;
	int m_timer_Point_Draw = 0;

	float m_drawTimer = 0.5f;
	int   m_drawState = 0; //0:クライム, 1:スター, 2:合計
	
	//ポイント
	FontRender   m_fontRender_star_Point;
	FontRender   m_fontRender_climb_Point;
	FontRender   m_fontRender_climb_Product;
	FontRender   m_fontRender_star_Product;
	FontRender   m_fontRender_total_Point;
	FontRender   m_fontRender_skip;
	FontRender   m_fontRender_timer;
	
	SoundSource* m_resultBGM;
	SoundSource* m_resultSE;

	Title* title;
	Score* score;
	Game* game;
	Player* player;
	
};

