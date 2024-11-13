#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position)
{

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
}

void Enemy::Update()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	move.z -= kCharacterSpeed;

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
