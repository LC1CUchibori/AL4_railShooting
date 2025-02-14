
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
	reel1_ = new Reel();
	// スロットリールの初期化
	reel1_->Initialize(modelReel_, &viewProjection_);

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
	// 左側のボタン生成
	button1_ = new Button();
	// 左側のボタンの初期化
	button1_->Initialize(modelButton_, &viewProjection_);
	// 左側のボタンの位置
	button1_->SetPosition({-3.0f, 0.0f, 0.0f});

	// 真ん中のボタンの生成
	button2_ = new Button();
	// 真ん中のボタンの初期化
	button2_->Initialize(modelButton_, &viewProjection_);
	// 真ん中のボタンの位置
	button2_->SetPosition({0.5f, 0.0f, 0.0f});
	
	// 右側のボタン生成
	button3_ = new Button();
	// 右側のボタンの初期化
	button3_->Initialize(modelButton_, &viewProjection_);
	// 右側のボタンの位置
	button3_->SetPosition({4.0f, 0.0f, 0.0f});
}

void GameScene::Update() {

	// スロットリール1
	reel1_->Update();
	// スロットリール2
	reel2_->Update();
	// スロットリール3
	reel3_->Update();

	// レバー
	lever_->Update();

	// ボタン1
	button1_->Update();
	// ボタン2
	button2_->Update();
	// ボタン3
	button3_->Update();

	// 現在の状態を保存
	static int currentButtonIndex = 0;
	static int pressCount = 0; // 何回ボタンを押したかを数える変数

#pragma region レバーの処理
	// レバーが引かれていたらリール回転開始
	if (lever_->IsPulled())
	{
		reel1_->StartRotation();
		reel2_->StartRotation();
		reel3_->StartRotation();

		// レバーを引いたらボタン押しの進行もリセットする
		currentButtonIndex = 0;
		pressCount = 0;
	}
#pragma endregion

#pragma region ボタンの処理
	// キー入力
	Input* input = Input::GetInstance();

	// スペースキーを押したら、左から順にボタンを押す
	if (input->TriggerKey(DIK_SPACE))
	{
		switch (currentButtonIndex)
		{
		case 0:
			button1_->Press();
			reel1_->StopRotation(); // ここでリール止める
			break;
		case 1:
			button2_->Press();
			reel2_->StopRotation(); // ここでリール止める
			break;
		case 2:
			button3_->Press();
			reel3_->StopRotation(); // ここでリール止める
			break;
		}

		// 次のボタンへ
		currentButtonIndex++;
		pressCount++;

		// 3回押したらリセットする
		if (pressCount >= 3)
		{
			currentButtonIndex = 0; // 左に戻る
			pressCount = 0;         // カウントもリセット
		}
	}
#pragma endregion
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
	reel1_->Draw();
	// スロットリール2
	reel2_->Draw();
	// スロットリール3
	reel3_->Draw();

	// レバー
	lever_->Draw();

	// レバーパーツ
	leverParts_->Draw();

	// ボタン1
	button2_->Draw();
	// ボタン2
	button3_->Draw();
	// ボタン3
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
