#include "TitleScene.h"
#include <numbers>

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

	TitleHandle_ = TextureManager::Load("Title.png");
	titleSprite_ = Sprite::Create(TitleHandle_, { 0,0 });
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

	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	titleSprite_->Draw();

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}