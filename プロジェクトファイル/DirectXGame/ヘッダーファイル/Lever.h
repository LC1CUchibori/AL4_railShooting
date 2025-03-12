#pragma once

#include "Audio.h"

class Lever
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update(int &medal, int&gameCont);

    void Draw();

    bool IsPulled() const
    {
        return downTimer_ > 0;
    }

private:
    Audio *audio_ = nullptr;

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

    //サウンドデータハンドル
    uint32_t LEVER = 0;

    //音声再生ハンドル
    uint32_t voiceHandle_ = 0;

    bool isPulled_ = false;
};

