#pragma once
#include "sound/SoundSource.h"

class Score;
class GameCamera;
class Transform;

class Player:public IGameObject
{
public:
	Player();   //コンストラクタ　　NewGOした時に使うがStartを使ったほうがいい
	~Player();  //～はデストラクタ　DeleteGOをした時に呼ばれる
	bool Start() override;
	void Update();
	//描画処理
	void Render(RenderContext& renderContext);
	//移動処理
	void Move();
	//回転処理
	void Rotation();

		
	const Vector3& GetPosition();
	///<summary>
	///	移動速度を加算
	/// </summary>
	/// <param name="addMoveSpeed">加算する移動速度</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	///<summary>
	///	キャラクターコントローラー
	/// </summary>
	/// <returns>キャラクターコントローラー</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


	//ここからメンバ変数
	ModelRender m_modelRender;
	Vector3 m_initialPosition;
	enum EnAnimationClip {//アニメーション
		enAnimationClip_Idle,
		//enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Vector3 m_moveSpeed;
	int m_playerState = 0; 
	

	Score* score;
	SoundSource* jumpSE;
	GameCamera* m_gameCamera;
	Transform* m_transform=nullptr;
	
	float m_alpha = 1.0f; //透明度

	Transform* GetTransform()
	{
		return m_transform;
	}

	void ReleaseParent();
};

