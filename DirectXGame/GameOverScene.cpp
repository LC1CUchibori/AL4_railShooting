#include "GameOverScene.h"
#include <numbers>

void GameOverScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

	GameOverHandle_ = TextureManager::Load("GameOver.png");
	gameOverSprite_ = Sprite::Create(GameOverHandle_, { 0,0 });
}

void GameOverScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void GameOverScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);


	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	gameOverSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}