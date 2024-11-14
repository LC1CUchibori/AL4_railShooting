#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "EnemyAnswer.h"
#include "Skydome.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollision();

	bool isDebugCameraActiv_ = false;

	bool IsFinished() const { return finished_; }


private: // メンバ変数

	enum class EnemyState {
		O,  // 〇の状態
		X   // ×の状態
	};

	enum class GamePhase {
		Phase1,    // フェーズ1
		Phase2,    // フェーズ2
		Phase3,    // フェーズ3
		Phase4,    // フェーズ4
		Phase5,    // フェーズ5
		Complete   // 完了
	};

	// 初期の状態を〇に設定
	EnemyState state_ = EnemyState::O;
	// 初期フェーズをPhase1に設定
	GamePhase phase_ = GamePhase::Phase1;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;
	// 3Dモデル
	Model* modelSkydome_ = nullptr;

	// 敵
	EnemyAnswer* enemy_ = nullptr;
	EnemyAnswer* enemy2_ = nullptr;

	// モデル
	Model* modelO_ = nullptr;
	Model* modelX_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool debugCameraFlag_ = false;

	bool finished_ = false;

	std::vector<EnemyAnswer> enemies_;
	Model* enemyModel_ = nullptr;

	void CheckNextPhaseO();

	void CheckNextPhaseX();

	void ResetPosition();


};