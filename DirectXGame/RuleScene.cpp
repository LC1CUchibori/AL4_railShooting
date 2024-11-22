#include "RuleScene.h"
#include <numbers>



RuleScene::~RuleScene() {
	delete ruleSprite_;
}

void RuleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	titleWorldTransform_.Initialize();
	viewProjection_.Initialize();

	RuleHandle_ = TextureManager::Load("Rule.png");
	ruleSprite_ = Sprite::Create(RuleHandle_, { 0,0 });
}

void RuleScene::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void RuleScene::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Model::PreDraw(commandList);


	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	ruleSprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

}