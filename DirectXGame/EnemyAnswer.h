#pragma once
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
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 移動時間のカウント
	float moveTimer_ = 0.0f;

	// 方向変更のインターバル（秒）
	float changeInterval_ = 2.0f;

	const float kCharacterSpeed = 0.05f;  // 移動速度調整

	Vector3 moveDirection_ = { 0.0f, 0.0f, 0.0f };

	// フェーズ
	//Phase phase_ = Phase::Approach;

	//// 接近フェーズの移動
	//const float ApproachSpeed = 0.1f;
	//// 離脱フェーズの移動
	//const float LeaveSpeed = 0.2f;
};