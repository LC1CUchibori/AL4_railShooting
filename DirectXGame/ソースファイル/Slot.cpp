#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Slot.h"

void Slot::Initialize(Model *model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	modelLeverParts_ = model;
}

void Slot::Update()
{
}

void Slot::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);

	modelLeverParts_->Draw(worldTransform_, *viewProjection_);
}
