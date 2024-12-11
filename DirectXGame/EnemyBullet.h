#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"WorldTransformBlock.h"

class EnemyBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	void OnCollision();

	Vector3 GetWorldPosition()const { return worldTransform_.translation_; }

	bool IsDead()const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 速度
	Vector3 velocity_;

	// 寿命
	static const int32_t klifeTime = 60 * 2;
	// デスタイマー
	int32_t deathTimer_ = klifeTime;
	// デスフラグ
	bool isDead_ = false;
};

