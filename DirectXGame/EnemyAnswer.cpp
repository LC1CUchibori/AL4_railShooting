#include "EnemyAnswer.h"
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <algorithm>

enum class MovePhase {
    Approach, // 接近フェーズ
    RandomMove // ランダム移動フェーズ
};

void EnemyAnswer::Initialize(Model* model, const Vector3& position)
{
    model_ = model;
    textureHandle_ = TextureManager::Load("white1x1.png");
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;

    // ランダムシードの設定
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 移動開始からの経過時間
    moveTimer_ = 0.0f;
   
    changeInterval_ = 2.0f;  

    // 接近フェーズから開始
    movePhase_ = MovePhase::Approach;

    // 接近時の移動速度
    approachSpeed_ = 0.1f;

    // ランダム移動の開始位置 (敵が停止する位置)
    stopPosition_ = Vector3{0.0f, 0.0f, -1.0f};
}

void EnemyAnswer::Update()
{
    // 行列を更新
    worldTransform_.UpdateMatrix();

    // 現在のフェーズに応じて動作を変更
    if (movePhase_ == MovePhase::Approach)
    {
        // 手前から反対方向に向かって移動する（z軸の奥方向に進む）
        worldTransform_.translation_.z -= approachSpeed_;

        // 一定の位置に到達したらランダム移動フェーズに切り替え
        if (worldTransform_.translation_.z <= stopPosition_.z)
        {
            movePhase_ = MovePhase::RandomMove;
            moveTimer_ = 0.0f;  // タイマーリセット
        }
    }
    else if (movePhase_ == MovePhase::RandomMove)
    {
        // ランダム移動フェーズの処理
        moveTimer_ += 1.0f / 60.0f;  // フレームレートを仮定して加算

        // 一定時間経過したら方向を変更
        if (moveTimer_ >= changeInterval_)
        {
            ChangeDirection();
            moveTimer_ = 0.0f;  // タイマーリセット
        }

        // 現在の移動方向に基づいて移動
        worldTransform_.translation_.x += moveDirection_.x * kCharacterSpeed;
        worldTransform_.translation_.y += moveDirection_.y * kCharacterSpeed;
        worldTransform_.translation_.z += moveDirection_.z * kCharacterSpeed;

        // 画面範囲内に収まるように制限
        const float kLimit = 5.0f;
        worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kLimit, kLimit);
        worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kLimit, kLimit);
        worldTransform_.translation_.z = std::clamp(worldTransform_.translation_.z, -kLimit, kLimit);
    }

    // z座標を少し奥に変更す
    worldTransform_.translation_.z -= 10.0f;


}

void EnemyAnswer::Draw(const ViewProjection& viewProjection)
{
    model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

// ランダムな移動方向を変更する関数
void EnemyAnswer::ChangeDirection()
{
    // ランダムな方向を設定 (-1.0 ~ 1.0 の範囲)
    moveDirection_ = {
        static_cast<float>(std::rand() % 2001 - 1000) / 1000.0f,  // -1.0 ~ 1.0
        static_cast<float>(std::rand() % 2001 - 1000) / 1000.0f,  // -1.0 ~ 1.0
        static_cast<float>(std::rand() % 2001 - 1000) / 1000.0f   // -1.0 ~ 1.0
    };
}

