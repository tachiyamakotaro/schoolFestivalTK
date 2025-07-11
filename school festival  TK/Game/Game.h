#pragma once
#include "sound/SoundSource.h"

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class MovingFloor;
class DownFloor;
class Score;
class Result;
class Title;
class Star;
class FreelyFloor;

class Game : public IGameObject
{
public:
	Game();
	
	
	~Game();
	bool Start();
	void Update();
	void MovingObj(Vector3 pos);
	void DownObj(Vector3 pos);
	void Render(RenderContext& rc);
	void MakeStar(Vector3 pos);
	void FreelyObj(Vector3 pos);
	
	FontRender m_fontRender;
	FontRender m_timeFontRender;
	BackGround* backGround;  //背景
	GameCamera* gameCamera;
	Player* m_player;
	MovingFloor* movingFloor;
	DownFloor* downFloor;
	Score* score;
	Result* result;
	Star* star;
	
	
	//時間制限
	float m_timer = 120.0f;

	SoundSource* m_gameBGM;
	std::vector<Star*>m_stars;

	ModelRender m_modelRender;
	Vector3 m_pos;
	PhysicsStaticObject m_physicsStaticObject;
	ModelRender m_backGround;
	int m_starCount = 0;
	//float m_timerText;
	SkyCube* m_skyCube = nullptr;//スカイキューブ(空の実装)
	int m_skyCubeType = enSkyCubeType_DayToon;//空の種類
};

