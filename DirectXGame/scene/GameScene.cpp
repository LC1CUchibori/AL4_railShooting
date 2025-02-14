
#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	delete modelSlot_;
	delete modelReel_;
	delete modelReel2_;
	delete modelReel3_;
	delete modelLeverParts_;
	delete modelLever_;
	delete modelButton_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	
	// モデル生成
	modelSlot_ = Model::CreateFromOBJ("Slot", true);
	// スロットの生成
	slot_ = new Slot();
	// スロットの初期化
	slot_->Initialize(modelSlot_, &viewProjection_);

	// モデル生成
	modelReel_ = Model::CreateFromOBJ("Reel", true);
	// スロットリールの生成
	reel_ = new Reel();
	// スロットリールの初期化
	reel_->Initialize(modelReel_, &viewProjection_);

	// モデル生成
	modelReel2_ = Model::CreateFromOBJ("Reel2", true);
	// スロットリール2の生成
	reel2_ = new Reel2();
	// スロットリール2の初期化
	reel2_->Initialize(modelReel2_, &viewProjection_);

	// モデル生成
	modelReel3_ = Model::CreateFromOBJ("Reel3", true);
	// スロットリール3の生成
	reel3_ = new Reel3();
	// スロットリー3の初期化
	reel3_->Initialize(modelReel3_, &viewProjection_);

	// モデル生成
	modelLever_ = Model::CreateFromOBJ("Lever", true);
	// レバーの生成
	lever_ = new Lever();
	// レバーの初期化
	lever_->Initialize(modelLever_, &viewProjection_);

	// モデル生成
	modelLeverParts_ = Model::CreateFromOBJ("LeverParts", true);
	// レバーパーツの生成
	leverParts_ = new Slot();
	// レバーパーツの初期化
	leverParts_->Initialize(modelLeverParts_, &viewProjection_);

	// モデルの生成
	modelButton_ = Model::CreateFromOBJ("Botan", true);
	// ボタン1の生成・初期化
	button1_ = new Button();
	button1_->Initialize(modelButton_, &viewProjection_);
	
}

void GameScene::Update() {

	// スロットリール1
	reel_->Update();

	// スロットリール2
	reel2_->Update();

	// スロットリール3
	reel3_->Update();

	// レバー
	lever_->Update();

	// ボタン
	button1_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// スロット鏡台
	slot_->Draw();

	// スロットリール1
	reel_->Draw();

	// スロットリール2
	reel2_->Draw();

	// スロットリール3
	reel3_->Draw();

	// レバー
	lever_->Draw();

	// レバーパーツ
	leverParts_->Draw();

	// ボタン
	button1_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
