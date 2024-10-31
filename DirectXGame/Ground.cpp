#include "Ground.h"

void Ground::Initialize(Model *model, ViewProjection* viewProjection) { 

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Ground::Update() {}

void Ground::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}