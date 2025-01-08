#include "Enemy.h"
#include <cassert>
#include <MyMath.h>
#include "Player.h"
#include <algorithm>

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
    textureHandle_ = TextureManager::Load("white1x1.png");
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;

    // 初期位置を設定（奥に配置するためZを -100 に設定）
    worldTransform_.translation_ = { position.x, position.y, position.z + 30.0f };


    // ランダム移動用の初期化
    ChangeDirection();
    directionChangeTimer = kDirectionChangeInterval;

    // 発射タイマーの初期化
    fireTimer = kFIreInterval;

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

    // ランダム移動処理
    directionChangeTimer--;
    if (directionChangeTimer <= 0) {
        ChangeDirection();  // 新しい移動方向を設定
        directionChangeTimer = kDirectionChangeInterval;
    }

    // 現在の方向に移動
    worldTransform_.translation_ += moveDirection_;

    // 画面内の制約を守るよう調整
    ClampPosition();

    // 弾発射処理
    fireTimer--;
    if (fireTimer <= 0) {
        Fire();
        fireTimer = kFIreInterval;
    }

    // 弾の更新
    for (EnemyBullet* bullet : bullets_) {
        bullet->Update();
    }

    // 行列を更新
    worldTransform_.UpdateMatrix();
}

void Enemy::ClampPosition()
{
    // 画面内に敵を留める (仮の範囲 -50～50)
    worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -50.0f, 50.0f);
    worldTransform_.translation_.z = std::clamp(worldTransform_.translation_.z, -50.0f, 50.0f);
}

void Enemy::ChangeDirection()
{
    // ランダムな方向を生成 (-1.0f ～ 1.0f)
    moveDirection_ = Vector3(
        static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f,
        0.0f,  // 水平方向のみ
        static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f
    );

    // ベクトルの正規化と速度設定
    moveDirection_.Normalize(moveDirection_);
    moveDirection_ *= kMoveSpeed;  // 固定速度
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

void Enemy::OnCollision()
{
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

