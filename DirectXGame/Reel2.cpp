#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Reel2.h"

void Reel2::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel2::Update()
{
}

void Reel2::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
