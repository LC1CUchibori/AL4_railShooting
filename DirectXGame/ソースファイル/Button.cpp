#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Button.h"

void Button::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Button::Update()
{
	
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

}

void Button::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
