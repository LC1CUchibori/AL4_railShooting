#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Reel3.h"

void Reel3::Initialize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Reel3::Update()
{
}

void Reel3::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
#include "Reel3.h"
