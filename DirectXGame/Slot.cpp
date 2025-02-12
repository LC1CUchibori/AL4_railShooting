#include "Slot.h"

void Slot::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Slot::Update()
{
}

void Slot::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
