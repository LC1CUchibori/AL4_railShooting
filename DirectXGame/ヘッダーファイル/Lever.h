#pragma once
#include <GameScene.h>
#include <rand.h>



class Lever
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update(int &medal,int&gameCont);

    void Draw();

    bool IsPulled() const
    {
        return downTimer_ > 0;
    }

    int GetStorenum(){return storenum;}


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

    bool isPulled_ = false;


    Rand rng;

    int storenum = rng.GetRandamNumber(0,300);
};




