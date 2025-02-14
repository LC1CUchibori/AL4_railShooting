#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "ヘッダーファイル/Button.h"
#include <Input.h>

void Button::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Button::Update()
{

    // 押し込み状態の場合、経過時間をカウントし、所定の時間経過でリセットする
    if (isPressed_)
    {
        // ここでは簡易的に 1/60 秒分を加算
        const float deltaTime = 1.0f / 60.0f;
        pressTimer_ += deltaTime;
        if (pressTimer_ >= pressDuration_)
        {
            // 押し込み状態を解除し、元の位置に戻す
            worldTransform_.translation_.z = originalPosition_.z;
            isPressed_ = false;
        }
    }

    // ワールド行列を更新
    worldTransform_.UpdateMatrix();

    // ワールドトランスフォームの更新
    worldTransform_.UpdateMatrix();
}

void Button::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Button::Press()
{
    // ボタンを押したとき、Z 軸方向にオフセットを加える
    worldTransform_.translation_.z = originalPosition_.z + pressedOffset_;
    isPressed_ = true;
    pressTimer_ = 0.0f;
}

void Button::SetPosition(const Vector3& position)
{
	// ワールドトランスフォーム内の位置を更新
	worldTransform_.translation_ = position;
	// 初期位置も記録
	originalPosition_ = position;
}
