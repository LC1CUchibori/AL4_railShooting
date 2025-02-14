#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Reel.h"

void Reel::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel::Update()
{
}

void Reel::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
