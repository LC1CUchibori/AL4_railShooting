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

	

	// 行列を更新
	worldTransform_.UpdateMatrix();

	switch (phase_)
	{
	default:
	case Phase::Approach:
		// 移動
		/*worldTransform_.translation_.x -=ApproachSpeed;
		worldTransform_.translation_.y -=ApproachSpeed;*/
		worldTransform_.translation_.z -=ApproachSpeed;
		// 既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		// 移動
		/*worldTransform_.translation_.x -= LeaveSpeed;
		worldTransform_.translation_.y -= LeaveSpeed;*/
		worldTransform_.translation_.z -= LeaveSpeed;
		break;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
