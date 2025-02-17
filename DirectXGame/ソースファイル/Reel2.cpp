#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Reel2.h"

void Reel2::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel2::Update()
{
	// リールの位置を少し下に
	worldTransform_.translation_.y = -1.5f;

	if (isRotating_)
	{
		// Y軸周りに回転
		worldTransform_.rotation_.x += 0.1f;
	}
	else if (isStopping_)
	{
		// 一定速度で目標に向かう
		float& rotationX = worldTransform_.rotation_.x;
		float diff = stopTargetAngle_ - rotationX;

		// 目標角度に向かって進む
		if (fabs(diff) > 0.01f)
		{
			// 1フレームの回転量
			float step = (diff > 0 ? 0.1f : -0.1f);
			if (fabs(diff) < fabs(step))
			{
				step = diff;
			}
			rotationX += step;
		}
		else
		{
			// 差分が小さくなったら即停止
			rotationX = stopTargetAngle_;
			isStopping_ = false; // 停止
		}
	}

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Reel2::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Reel2::StopRotation()
{
	isRotating_ = false;

	const float symbolAngleRad = 36.0f * (3.14159265f / 180.0f);
	float& rotationX = worldTransform_.rotation_.x;

	// 0～2πの範囲に正規化
	rotationX = fmod(rotationX, 2.0f * 3.14159265f);

	float offsetAngle = symbolAngleRad * 0.6f; // 0.6個分 ちょっと進ませる
	float nextSymbolAngle = ceil(rotationX / symbolAngleRad) * symbolAngleRad + offsetAngle;

	// 目標角度に向けて一定速度で進むようにする
	stopTargetAngle_ = nextSymbolAngle;
	// 滑らかに止まる
	isStopping_ = true; 
}


