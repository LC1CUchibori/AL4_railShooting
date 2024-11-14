#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	delete player_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete enemy_;
	delete enemy2_;  
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);


	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 敵の生成
	enemy_ = new EnemyAnswer();
	// 敵の初期化
	enemy_->Initialize(model_,{-10.0f,1.0f,10.0f});

	// 敵2の生成と初期化
	enemy2_ = new EnemyAnswer();  // 新しい敵の生成
	enemy2_->Initialize(model_, {10.0f, 1.0f, 10.0f});


	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();

	// 天球の更新
	skydome_->Update();


	// 自キャラの旋回更新
	player_->Rotate();

	// デバッグカメラの更新
	debugCamera_->Update();

	CheckAllCollision();

	// 敵の更新
	enemy_->Update();
	// 敵2の更新
	enemy2_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		debugCameraFlag_ = true;
	}
#endif

	// カメラの処理
	if (debugCameraFlag_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行rの転送
		viewProjection_.TransferMatrix();
	}
	else {
		// ビュープロジェクション行列の更新転送
		viewProjection_.UpdateMatrix();
	}

	switch (phase_) {
	case GamePhase::Phase1:
		// フェーズ1の処理
		state_ = EnemyState::O;  // 〇が正解
		break;
	case GamePhase::Phase2:
		// フェーズ2の処理
		state_ = EnemyState::X;  // ×が正解
		break;
	case GamePhase::Phase3:
		// フェーズ3の処理
		state_ = EnemyState::O;  // 〇が正解
		break;
	case GamePhase::Phase4:
		// フェーズ4の処理
		state_ = EnemyState::X;  // ×が正解
		break;
	case GamePhase::Phase5:
		// フェーズ5の処理
		state_ = EnemyState::O;  // 〇が正解
		break;
	case GamePhase::Complete:
		// 完了フェーズ
		break;
	}
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
	// 3Dモデル描画
	//	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

	// 自キャラの描画
	player_->Draw();

	// 天球の描画
	skydome_->Draw();

	// 敵の描画

	enemy_->Draw(viewProjection_);
	// 敵2の描画
	enemy2_->Draw(viewProjection_);

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
}

void GameScene::CheckAllCollision()
{
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullet();

	posA = enemy_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();

		if (((posB.x - posA.x)*(posB.x - posA.x) + (posB.y - posA.y) *(posB.y - posA.y)  + (posB.z - posA.z) * (posB.z - posA.z) <= (1.0f + 1.0f) * (1.0f + 1.0f))) {
			enemy_->OnCollision();
			bullet->OnCollision();
			CheckNextPhaseO();
		}
	}


	// 敵2との衝突判定
	posB = enemy2_->GetWorldPosition();  // 敵2の位置
	for (PlayerBullet* bullet : playerBullets) {
		posA = bullet->GetWorldPosition();  // 弾の位置
		if (((posB.x - posA.x)*(posB.x - posA.x) + (posB.y - posA.y) *(posB.y - posA.y)  + (posB.z - posA.z) * (posB.z - posA.z) <= (1.0f + 1.0f) * (1.0f + 1.0f))) {
			bullet->OnCollision();
			enemy2_->OnCollision();
			CheckNextPhaseO();
		}
	}
	
}
void GameScene::CheckNextPhaseO()
{
	// 現在のフェーズに応じた判定
	if (phase_ == GamePhase::Complete) {
		return;  // 完了フェーズなので何もしない
	}

	// 敵を復活
	if (enemy_->IsDead()) {
		enemy_->Revive();
	}

	if (state_ == EnemyState::O) {
		// 〇を撃った場合

		// 次のフェーズに進む
		if (phase_ == GamePhase::Phase1) {
			phase_ = GamePhase::Phase2;
		}
		else if (phase_ == GamePhase::Phase2) {
			phase_ = GamePhase::Phase3;
		}
		else if (phase_ == GamePhase::Phase3) {
			phase_ = GamePhase::Phase4;
		}
		else if (phase_ == GamePhase::Phase4) {
			phase_ = GamePhase::Phase5;
		}
		else if (phase_ == GamePhase::Phase5) {
			phase_ = GamePhase::Complete;
		}
		// プレイヤーと敵の位置を初期位置にリセット
		ResetPosition();

	}
}
void GameScene::CheckNextPhaseX()
{
	if (enemy2_->IsDead()) {
		enemy2_->Revive();
	}

	if (state_ == EnemyState::X) {
		// ×を撃った場合

		// 次のフェーズに進む
		if (phase_ == GamePhase::Phase1) {
			phase_ = GamePhase::Phase2;
		}
		else if (phase_ == GamePhase::Phase2) {
			phase_ = GamePhase::Phase3;
		}
		else if (phase_ == GamePhase::Phase3) {
			phase_ = GamePhase::Phase4;
		}
		else if (phase_ == GamePhase::Phase4) {
			phase_ = GamePhase::Phase5;
		}
		else if (phase_ == GamePhase::Phase5) {
			phase_ = GamePhase::Complete;
		}
		// プレイヤーと敵の位置を初期位置にリセット
		ResetPosition();
	}
}
void GameScene::ResetPosition()
{
	// プレイヤーの初期位置を設定
	player_->SetPosition({ 0.0f, 1.0f, 0.0f });  // 初期位置の座標に変更

	// 敵の初期位置を設定
	enemy_->SetPosition({ -10.0f, 1.0f, 10.0f });  // 敵の初期位置に変更
	enemy2_->SetPosition({ 10.0f, 1.0f, 10.0f });  // 敵2の初期位置に変更
}
#pragma endregion