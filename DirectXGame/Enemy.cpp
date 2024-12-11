#include "Enemy.h"
#include <cassert>
#include <MyMath.h>
#include "Player.h"

Enemy::~Enemy()
{
	// bullet_の解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

	bullets_.clear();
}

void Enemy::Initialize(Model* model, const Vector3& position)
{

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	worldTransform_.translation_.x = 15.0f;
	worldTransform_.translation_.z = 50.0f;
	
	// 弾を発射
	//Fire();

	// 接近フェーズ初期化
	ApproachInitialize();
}

void Enemy::Update()
{

	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	switch (phase_)
	{
	case Phase::Approach:
		// 移動
		// 移動
		worldTransform_.translation_ -= Vector3(0, 0, 0.1f);
		// 既定の位置に到達したら離脱
		if (worldTransform_.translation_.z <10.0f) {
			phase_ = Phase::Leave;
		}
		// 発射タイマーカウントダウン
		fireTimer--;
		// 指定時間に達した
		if (fireTimer<=0) {
			// 弾を発射
			Fire();
			// 発射タイマーを初期化
			fireTimer = kFIreInterval;
		}
		break;
	case Phase::Leave:
		worldTransform_.translation_ += Vector3(-0.1f, 0.1f, -0.1f);
		
		break;
	}

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire()
{
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 0.03f;

	// 目キャラのワールド座標を取得する
	Vector3 playerPosition = player_->GetWorldPosition();

	// 敵キャラのワールド座標を取得する
	Vector3 enemyPosition = GetWorldPosition();


	// 敵キャラから目キャラへの差分ベクトルを求める
	Vector3 diff = playerPosition - enemyPosition;

	// ベクトルの正規化
	diff.Normalize(diff);

	// ベクトルの長さを速度に合わせる
	Vector3 velocity = diff * kBulletSpeed;

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_,velocity);

	// 弾を登録する
	bullets_.push_back(newBullet);
}

void Enemy::ApproachInitialize()
{
	// 発射タイマーを初期化
	fireTimer = kFIreInterval;
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得 (ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0]; 
	worldPos.y = worldTransform_.matWorld_.m[3][1]; 
	worldPos.z = worldTransform_.matWorld_.m[3][2]; 

	return worldPos;
}
