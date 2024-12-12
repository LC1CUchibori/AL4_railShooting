#include "Skydome.h"

void Skydome::Initalize(Model* model, ViewProjection* viewProjection);
{
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	model_->Draw(worldTransform_, viewProjection_);
}
