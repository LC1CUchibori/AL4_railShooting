#pragma once
#include "GameScene.h"

class DebugCamera {
public:
    DebugCamera(int width, int height);

    void Update();

    Matrix4x4 GetViewMatrix() { return viewProjection_->matView; }       // ビュー行列を取得
    Matrix4x4 GetProjectionMatrix() { return viewProjection_->matProjection; } // プロジェクション行列を取得

private:

    ViewProjection* viewProjection_ = nullptr;
};
