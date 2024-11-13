#include "EnemyAnswer.h"
#include <cstdlib> // rand, srand
#include <ctime>   // time

void EnemyAnswer::Initialize(Model* model, const Vector3& position)
{
    model_ = model;
    textureHandle_ = TextureManager::Load("white1x1.png");
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;

    // 乱数のシードを設定
    srand(static_cast<unsigned>(time(nullptr)));
}

void EnemyAnswer::Update()
{
    // 行列を更新
    worldTransform_.UpdateMatrix();

    // ランダムな移動量を生成
    float randomX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ApproachSpeed;
    float randomY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ApproachSpeed;
    float randomZ = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * ApproachSpeed;

    switch (phase_)
    {
    default:
    case Phase::Approach:
        // ランダムな方向に移動
        worldTransform_.translation_.x += randomX;
        worldTransform_.translation_.y += randomY;
        worldTransform_.translation_.z += randomZ;

        // 既定の位置に到達したら離脱フェーズへ
        if (worldTransform_.translation_.z < 0.0f) {
            phase_ = Phase::Leave;
        }
        break;
    case Phase::Leave:
        // 離脱フェーズでもランダムな移動量で離れていく
        worldTransform_.translation_.x += randomX * LeaveSpeed;
        worldTransform_.translation_.y += randomY * LeaveSpeed;
        worldTransform_.translation_.z -= LeaveSpeed;
        break;
    }
}

void EnemyAnswer::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}