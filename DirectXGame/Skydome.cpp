#include "Skydome.h"

void Skydome::Initalize()
{
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	model_->Draw(worldTransform_, viewProjection_);
}
