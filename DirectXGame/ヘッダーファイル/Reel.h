#pragma once
class Reel
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void StartRotation();

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

    float symbolAngle = 360.0f / 10.0f; // 36度

    bool isStopping_ = false; // 滑らか停止中フラグ
    float stopTargetAngle_ = 0.0f; // 止めたい最終角度
    float rotationSpeed_ = 0.1f;   // 現在の回転速度
};

