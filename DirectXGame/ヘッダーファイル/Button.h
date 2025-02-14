#pragma once
class Button
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    const WorldTransform& GetWorldTransform() const { return worldTransform_; }

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
};

