#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "WorldTransformBlock.h"
#include "Input.h"
#include "MyMath.h"
#include "PlayerBullet.h"
#include <list>


/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Rotate();

	void Attack();

	void OnCollision();

	// 弾
	std::list<PlayerBullet*>bullets_;

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;


	// キーボード入力
	Input* input_ = nullptr;

	PlayerBullet* bullet_ = nullptr;

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullet()const { return bullets_; }
};
