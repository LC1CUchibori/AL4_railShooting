#pragma once
class Reel2
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void StartRotation() { isRotating_ = true; }
    void StopRotation() { isRotating_ = false; }

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
};

