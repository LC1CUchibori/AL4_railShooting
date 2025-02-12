#include "Slot.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

void Slot::Initialize()
{
	// NULLチェック
	assert(model);

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void Slot::Update()
{
}

void Slot::Draw()
{
	model_->Draw();
}
