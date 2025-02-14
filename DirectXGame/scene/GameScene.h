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
	Reel* reel_ = nullptr;
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
};
