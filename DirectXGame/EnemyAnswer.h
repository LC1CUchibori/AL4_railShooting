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

	void OnCollision();

	// ワールド座標を取得するメソッド
	Vector3 GetWorldPosition() const {
		return worldTransform_.translation_;
	}

	void SetPosition(const Vector3& position);

	void Revive(); 

	bool IsDead()const { return isDead_; }

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

	const float kCharacterSpeed = 0.08f;  // 移動速度調整

	Vector3 moveDirection_ = { 0.0f, 0.0f, 0.0f };

	MovePhase movePhase_ = MovePhase::Approach;
	float approachSpeed_ = 0.01f;               // 接近時の移動速度
	Vector3 stopPosition_ = {0.0f, -10.0f, 10.0f}; // 停止位置

	// デスフラグ
	bool isDead_ = false;

	Vector3 initialPosition_;  // 敵の初期位置
};