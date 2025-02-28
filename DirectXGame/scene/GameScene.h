#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

#include "ヘッダーファイル/Slot.h"
#include "ヘッダーファイル/Reel.h"
#include "ヘッダーファイル/Reel2.h"
#include "ヘッダーファイル/Reel3.h"
#include "ヘッダーファイル/Lever.h"
#include "ヘッダーファイル/Button.h"
#include "ヘッダーファイル/PushButton.h"


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

	void DrawGameCount();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// スロット
	Slot* slot_ = nullptr;
	Model* modelSlot_ = nullptr;

	// スロットリール1
	Reel* reel1_ = nullptr;
	Model* modelReel_ = nullptr;
	// スロットリール2
	Reel2* reel2_ = nullptr;
	Model* modelReel2_ = nullptr;
	// スロットリール3
	Reel3* reel3_ = nullptr;
	Model* modelReel3_ = nullptr;

	// レバー
	Lever* lever_ = nullptr;
	Model* modelLever_ = nullptr;

	// レバーパーツ
	Slot* leverParts_ = nullptr;
	Model* modelLeverParts_ = nullptr;

	// ボタン1
	Button* button2_ = nullptr;
	// ボタン2
	Button* button3_ = nullptr;
	// ボタン3
	Button* button1_ = nullptr;
	Model* modelButton_ = nullptr;

	// Pushボタン
	PushButton* pushButton_ = nullptr;
	Model* modelPushButton_ = nullptr;

	bool reel1IsStopped_ = false;
	bool reel2IsStopped_ = false;
	bool reel3IsStopped_ = false;

	//メダル
	int Medal = 0;

	// ゲーム数
	int gameCount_ = 0;

	// 数字
	Sprite* sprite_[10];
	//テクスチャハンドル
	uint32_t TextureHandle_[10];

	// リールを動かせなくするフラグ
	bool Realflag = false;
};
