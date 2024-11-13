﻿#pragma once
#include <WorldTransform.h>
#include <Model.h>
class EnemyAnswer
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	// 最初のランダムな移動方向を決定
	void ChangeDirection();

	//enum class Phase
	//{
	//	Approach, // 接近する
	//	Leave,    // 離脱する
	//};

private:
	enum class MovePhase {
		Approach,    // 接近フェーズ
		RandomMove   // ランダム移動フェーズ
	};

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 移動時間のカウント
	float moveTimer_ = 0.0f;

	float changeInterval_ = 2.0f;

	const float kCharacterSpeed = 0.05f;  // 移動速度調整

	Vector3 moveDirection_ = { 0.0f, 0.0f, 0.0f };

	MovePhase movePhase_ = MovePhase::Approach;
	float approachSpeed_ = 0.01f;               // 接近時の移動速度
	Vector3 stopPosition_ = {0.0f, 0.0f, -1.0f}; // 停止位置
};