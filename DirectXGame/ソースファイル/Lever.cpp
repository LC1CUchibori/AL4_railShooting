#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
#include "ヘッダーファイル/Lever.h"
#include "Sprite.h"

void Lever::Initialize(Model *model, ViewProjection* viewProjection)
{
	input_ = Input::GetInstance();

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Lever::Update(int &medal,int&gameCount)
{
    // エンターキーが押されたらタイマー開始
    if (input_->TriggerKey(DIK_RETURN)) {
        downTimer_ = DownTime;
        storenum = rng.GetRandamNumber(1,300);
        if (medal >= 3) {
            medal -= 3;
        }
        gameCount+= 1;
    }

    // タイマーが残っている間は下げる
    if (downTimer_ > 0) {
        worldTransform_.translation_.y = DownOffsetY;
        downTimer_--;
    } else{
        worldTransform_.translation_.y = 0.0f;
    }

    //0以下にならないようにする処理
    if (medal < 0) {
        medal = 0;
    }

    worldTransform_.UpdateMatrix();

    std::cout<<"ランダム"<<storenum<<std::endl;
}

void Lever::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}