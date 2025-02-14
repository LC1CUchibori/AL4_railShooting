﻿#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Reel3.h"

void Reel3::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel3::Update()
{
	// Y軸周りに回転（例: 毎フレーム少しずつ回す）
	worldTransform_.rotation_.x += 0.1f;

	// リールの位置を少し下に
	worldTransform_.translation_.y = -1.5f;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

}

void Reel3::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

