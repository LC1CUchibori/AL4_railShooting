﻿#pragma once

class Slot
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    Model* modelLeverParts_ = nullptr;
};