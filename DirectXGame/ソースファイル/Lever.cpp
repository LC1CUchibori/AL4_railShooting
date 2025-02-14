#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
#include "ヘッダーファイル/Lever.h"

void Lever::Initialize(Model *model, ViewProjection* viewProjection)
{
	input_ = Input::GetInstance();

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Lever::Update()
{
    // スペースキーが押されたらタイマー開始
    if (input_->TriggerKey(DIK_RETURN)) {
        downTimer_ = DownTime;
    }

    // タイマーが残っている間は下げる
    if (downTimer_ > 0) {
        worldTransform_.translation_.y = DownOffsetY;
        downTimer_--;
    } else{
        worldTransform_.translation_.y = 0.0f;
    }

    worldTransform_.UpdateMatrix();
}

void Lever::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}


