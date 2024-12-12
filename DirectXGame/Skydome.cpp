#include "Skydome.h"



void Skydome::Initalize(Model* model, ViewProjection* viewProjection)
{

	dxCommon_ = DirectXCommon::GetInstance();
	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelSkydome_ = model;
	viewProjection_ = viewProjection;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	modelSkydome_->Draw(worldTransform_,*viewProjection_);
}
