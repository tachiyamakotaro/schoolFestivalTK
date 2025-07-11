#pragma once

class Player;
class Star;
class Game;
class Result;

class Score:public IGameObject
{
public:
	Score();
	~Score();

	bool Start();
	void Render(RenderContext& rc);
	void Update();
	void StarScore();
	void climbScore();
	void Rank();
	//void Point();

	


	//スターのカウント
	int m_starCount = 0;
	int m_climbCount = 0;
	
	FontRender m_fontRender_star;
	FontRender m_fontRender_climb;
	Player* player;
	Game* game;
	Result* result;
};

