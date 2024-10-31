#include "Ground.h"

void Ground::Initialize(Model *model, ViewProjection* viewProjection) { 

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.translation_.y = -0.1f;

}

void Ground::Update() {
	// ワールド行列の計算
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 定数バッファに転送する
	worldTransform_.TransferMatrix();
}

void Ground::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}