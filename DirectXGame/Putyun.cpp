#include "Putyun.h"
#include <cmath> // もし、必要ならmath.hなどをインクルード
#include <PrimitiveDrawer.h>

// コンストラクタ（初期化）
PlchunEffect::PlchunEffect() : isActive_(false), scale_(1.0f), maxScale_(1.5f), scaleSpeed_(0.05f), position_{ 400.0f, 300.0f }, color_{ 255, 255, 255 } {
}

// 初期化処理
void PlchunEffect::Initialize() {
    // 必要なリソースを初期化（必要ならば）
}

// エフェクトの更新
void PlchunEffect::Update() {
    if (isActive_) {
        // エフェクトのスケールを増加させ、その後元に戻す
        if (scale_ < maxScale_) {
            scale_ += scaleSpeed_;  // 拡大
        } else {
            scale_ -= scaleSpeed_;  // 元に戻す
            if (scale_ <= 1.0f) {
                isActive_ = false;  // エフェクト終了
            }
        }
    }
}

// エフェクトの描画
void PlchunEffect::Draw() {
    if (isActive_) {
        // 拡大した円を描画（円のサイズはscaleに応じて変化）
        DrawCircle(position_.x, position_.y, 50 * scale_, color_);
    }
}

// スペースキーでエフェクトを発動
void PlchunEffect::Trigger() {
    isActive_ = true;
}

// 円を描画する関数
void PlchunEffect::DrawCircle(float x, float y, float radius, Color color) {
    PrimitiveDrawer* primitiveDrawer = PrimitiveDrawer::GetInstance();
}
