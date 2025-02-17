#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Reel.h"

void Reel::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel::Update()
{

	// リールの位置を少し下に
	worldTransform_.translation_.y = -1.5f;

	if (isRotating_)
	{
		// Y軸周りに回転
		worldTransform_.rotation_.x += 0.1f;
	}

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

}

void Reel::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Reel::StopRotation()
{
	isRotating_ = false;

	const float symbolAngleRad = 36.0f * (3.14159265f / 180.0f);
	float& rotationX = worldTransform_.rotation_.x;

	// 0～2πの範囲に正規化
	rotationX = fmod(rotationX, 2.0f * 3.14159265f);

	float nearestStopAngle = round(rotationX / symbolAngleRad) * symbolAngleRad;

	// 半個分(= 1/2) 上にズラす
	nearestStopAngle -= symbolAngleRad * 0.4f;

	rotationX = nearestStopAngle;
}

