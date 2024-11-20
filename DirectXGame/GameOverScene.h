#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GameScene.h"
/// <summary>
/// タイトルシーン
/// </summary>
class GameOverScene {
public:
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

	bool IsFinished() const { return finished_; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	WorldTransform titleWorldTransform_;
	ViewProjection viewProjection_;

	bool finished_ = false;
};