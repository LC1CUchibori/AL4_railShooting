#include "Boss.h"

void Boss::Initialize(Model *model, ViewProjection* viewProjection) { 

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.scale_ = { 15.0f,15.0f,15.0f };
}

void Boss::Update() {
	worldTransform_.UpdateMatrix();
}

void Boss::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}