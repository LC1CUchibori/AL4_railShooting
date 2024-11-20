#include "GameOverScene.h"
#include <numbers>

void GameOverScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

}

void GameOverScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void GameOverScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);


	Model::PostDraw();

}