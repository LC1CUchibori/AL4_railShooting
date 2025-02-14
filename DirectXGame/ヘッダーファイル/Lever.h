#pragma once
class Lever
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    bool IsPressed() const { return downTimer_ > 0; }

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    Input* input_ = nullptr;

    const float DownOffsetY = -0.2f; // 下がる距離
    const int DownTime = 10;         // 下がっている時間
    int downTimer_ = 0;              // 下がり時間カウント
};

