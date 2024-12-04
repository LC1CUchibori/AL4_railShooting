﻿//#pragma once
//
//#include "Model.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include"WorldTransformBlock.h"
//
//class EnemyBullet
//{
//public:
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize(Model* model, const Vector3& position);
//
//	/// <summary>
//	/// 更新
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// 描画
//	/// </summary>
//	void Draw(const ViewProjection& viewProjection);
//
//	bool IsDead()const { return isDead_; }
//
//private:
//	// ワールド変換データ
//	WorldTransform worldTransform_;
//	// モデル
//	Model* model_ = nullptr;
//	// テクスチャハンドル
//	uint32_t textureHandle_ = 0;
//
//	// 寿命
//	static const int32_t klifeTime = 60 * 5;
//	// デスタイマー
//	int32_t deathTimer_ = klifeTime;
//	// デスフラグ
//	bool isDead_ = false;
//};
//