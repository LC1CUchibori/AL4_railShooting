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

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

}

void Reel2::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
