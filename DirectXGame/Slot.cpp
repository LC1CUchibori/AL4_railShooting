#include "Slot.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

void Slot::Initialize(Model* model, ViewProjection* viewProjection)
{
	// NULLチェック
	assert(model);

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
