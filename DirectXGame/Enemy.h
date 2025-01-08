#pragma once
#include <WorldTransform.h>
#include <Model.h>
#include <EnemyBullet.h>

// 自爆クラス
class Player;

class Enemy
{
public:
	~Enemy();

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void ChangeDirection();

	void ClampPosition();

	enum class Phase
	{
		Approach, // 接近する
		Leave,    // 離脱する
	};

	void Fire();

	void OnCollision();

	// 接近フェーズ初期化
	void ApproachInitialize();
	// 発射間隔
	static const int kFIreInterval = 60;

	void SetPlayer(Player* player) { player_ = player; }

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets()const { return bullets_; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

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

	int32_t directionChangeTimer = 0;
	const int32_t kDirectionChangeInterval = 60;
	Vector3 moveDirection_;
	float kMoveSpeed = 0.1f;

	// 発射タイマー
	int32_t fireTimer = 0;

	// 弾丸のリスト
	std::list<EnemyBullet*> bullets_;

	// 自キャラ
	Player* player_ = nullptr;

	Enemy* enemy_ = nullptr;


};