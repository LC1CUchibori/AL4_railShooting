﻿#include "Skydome.h"

void Skydome::Initialize(Model *model, ViewProjection* viewProjection) { 

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.scale_ = { 2.0f,2.0f,2.0f };
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
