#include "Enemy.h"
#include <cassert>
#include <MyMath.h>

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
	worldTransform_.translation_.z = 20.0f;
	
	Fire();
}

void Enemy::Update()
{
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

	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, -kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_,velocity);

	// 弾を登録する
	bullets_.push_back(newBullet);
}
