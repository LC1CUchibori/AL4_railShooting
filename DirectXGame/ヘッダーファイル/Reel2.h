#pragma once
class Reel2
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void StartRotation() { isRotating_ = true; }

    void StopRotation();

    bool IsRotating() const { return isRotating_; }

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    // 回転してるかのフラグ
    bool isRotating_ = false;

    float symbolAngle = 360.0f / 10.0f; // → 36度
};

