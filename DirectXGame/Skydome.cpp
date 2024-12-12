#include "Skydome.h"



void Skydome::Initalize()
{

	dxCommon_ = DirectXCommon::GetInstance();
	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void Skydome::Update()
{
}

void Skydome::Draw()
{
	modelSkydome_->Draw(worldTransform_,viewProjection_);
}
