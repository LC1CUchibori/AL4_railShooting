#include "TitleScene.h"
#include <numbers>

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

	BgHandle_ = TextureManager::Load("BG.png");
	bgSprite_ = Sprite::Create(BgHandle_, {0,0});

	TitleHandle_ = TextureManager::Load("title.png");
	titleSprite_ = Sprite::Create(TitleHandle_, { 160,50 });

}

void TitleScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void TitleScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);

	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	bgSprite_->Draw();
	titleSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}