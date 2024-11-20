#include "TitleScene.h"
#include <numbers>

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

}

void TitleScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
}

void TitleScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);


	Model::PostDraw();

}