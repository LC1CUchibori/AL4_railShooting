#pragma once
class Button
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void Press();

    const WorldTransform& GetWorldTransform() const { return worldTransform_; }

    void SetPosition(const Vector3& position);

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
    // ボタンの初期位置
    Vector3 originalPosition_;

    // 押し込み状態フラグ
    bool isPressed_ = false;
    float pressTimer_ = 0.0f;
    // 押し込みの持続時間
    const float pressDuration_ = 0.2f;
    // 押し込みの深さ
    const float pressedOffset_ = 0.13f;
};

