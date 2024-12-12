#include "Skydome.h"



void Skydome::Initalize(Model* model, ViewProjection* viewProjection)
{
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Skydome::Update()
{
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw()
{
	model_->Draw(viewProjection_);
}
