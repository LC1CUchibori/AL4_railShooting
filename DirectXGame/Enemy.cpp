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
	worldTransform_.translation_.z = 15.0f;
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

	// 行列を更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
