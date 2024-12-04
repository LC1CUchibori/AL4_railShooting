#pragma once
#include <WorldTransform.h>
#include <Model.h>
class Enemy
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	enum class Phase
	{
		Approach, // 接近する
		Leave,    // 離脱する
	};

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 接近フェーズの移動
	const float ApproachSpeed = 0.1f;
	// 離脱フェーズの移動
	const float LeaveSpeed = 0.1f;
};