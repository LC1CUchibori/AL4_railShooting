#include "GameClearScene.h"
#include <numbers>

void GameClearScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

	ClearHandle_ = TextureManager::Load("BGClear.png");
	ClearSprite_ = Sprite::Create(ClearHandle_, { 0,0 });
}

void GameClearScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void GameClearScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);

	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	ClearSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}