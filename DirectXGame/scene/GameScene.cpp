#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include <ImGuiManager.h>


GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	delete player_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete enemy_;
	delete enemy2_;  
	delete Q1sprite_;
	delete HealthSprite1_;
	delete HealthSprite2_; 
	delete HealthSprite3_;
	delete modelBoss_;
	delete modelHumanBoss_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 問題１
	Q1Handle_ = TextureManager::Load("Q1.png");
	Q1sprite_ = Sprite::Create(Q1Handle_, { 100,50 });

	// 体力1
	HealthHandle1_ = TextureManager::Load("Health.png");
	HealthSprite1_ = Sprite::Create(HealthHandle1_, { 100,600 });
	// 体力2
	HealthHandle2_ = TextureManager::Load("Health.png");
	HealthSprite2_ = Sprite::Create(HealthHandle2_, { 140,600 });
	// 体力3
	HealthHandle3_ = TextureManager::Load("Health.png");
	HealthSprite3_ = Sprite::Create(HealthHandle3_, { 180,600 });


	boss_ = new Boss();
	modelBoss_ = Model::CreateFromOBJ("TV", true);
	boss_->Initialize(modelBoss_, &viewProjection_);

	humanBoss_ = new HumanBoss();
	modelHumanBoss_ = Model::CreateFromOBJ("kao", true);
	humanBoss_->Initialize(modelHumanBoss_, &viewProjection_);

	// 自キャラの生成
	player_ = new Player();
	//model_ = Model::CreateFromOBJ("perikann",true);
	// 自キャラの初期化
	player_->Initialize(model_, &viewProjection_);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);


	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	modelO_ = Model::CreateFromOBJ("maru", true);
	modelX_ = Model::CreateFromOBJ("X", true);

	// 敵の生成
	enemy_ = new EnemyAnswer();
	// 敵の初期化
	enemy_->Initialize(modelO_,{-10.0f,1.0f,10.0f});

	// 敵2の生成と初期化
	enemy2_ = new EnemyAnswer();  // 新しい敵の生成
	enemy2_->Initialize(modelX_, {10.0f, 1.0f, 10.0f});



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

	if (NextPhaseFlag == false) {
		// 敵の更新
		enemy_->Update();
		// 敵2の更新
		enemy2_->Update();
	}
	if (NextPhaseFlag == true) {
		NextPhaseTimer -= 1;
		if (NextPhaseTimer <= 0) {
			NextPhaseFlag = false;
		}
	}




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


	const char* phaseName = "Phase 1";
	switch (phase_) {
	case GamePhase::Phase1:
		// フェーズ1の処理
		state_ = EnemyState::O;  // 〇が正解
		phaseName = "Phase 1";
		break;
	case GamePhase::Phase2:
		// フェーズ2の処理
		state_ = EnemyState::X;  // ×が正解
		phaseName = "Phase 2";
		break;
	case GamePhase::Phase3:
		// フェーズ3の処理
		state_ = EnemyState::O;  // 〇が正解
		phaseName = "Phase 3";
		break;
	case GamePhase::Phase4:
		// フェーズ4の処理
		state_ = EnemyState::X;  // ×が正解
		phaseName = "Phase 4";
		break;
	case GamePhase::Phase5:
		// フェーズ5の処理
		state_ = EnemyState::O;  // 〇が正解
		phaseName = "Phase 5";
		break;
	case GamePhase::Complete:
		// 完了フェーズ
		break;
	}

	ImGui::Begin("Game Phase");  // ウィンドウのタイトル
	ImGui::Text("Current Phase: %s", phaseName);  // フェーズ名を表示
	ImGui::Text("miss Count %d", missCount_);
	ImGui::End();
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

	boss_->Draw();

	humanBoss_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (phase_)
	{
	case GameScene::GamePhase::Phase1:
		Q1sprite_->Draw();
		if (Health1Flag == false) {
			HealthSprite1_->Draw();
		}
		if (Health2Flag == false) {
			HealthSprite2_->Draw();
		}
		if (Health3Flag == false) {
			HealthSprite3_->Draw();
		}
		break;
	case GameScene::GamePhase::Phase2:
		if (Health1Flag == false) {
			HealthSprite1_->Draw();
		}
		if (Health2Flag == false) {
			HealthSprite2_->Draw();
		}
		if (Health3Flag == false) {
			HealthSprite3_->Draw();
		}
		break;
	case GameScene::GamePhase::Phase3:
		if (Health1Flag == false) {
			HealthSprite1_->Draw();
		}
		if (Health2Flag == false) {
			HealthSprite2_->Draw();
		}
		if (Health3Flag == false) {
			HealthSprite3_->Draw();
		}
		break;
	case GameScene::GamePhase::Phase4:
		if (Health1Flag == false) {
			HealthSprite1_->Draw();
		}
		if (Health2Flag == false) {
			HealthSprite2_->Draw();
		}
		if (Health3Flag == false) {
			HealthSprite3_->Draw();
		}
		break;
	case GameScene::GamePhase::Phase5:
		if (Health1Flag == false) {
			HealthSprite1_->Draw();
		}
		if (Health2Flag == false) {
			HealthSprite2_->Draw();
		}
		if (Health3Flag == false) {
			HealthSprite3_->Draw();
		}
		break;
	case GameScene::GamePhase::Complete:
		break;
	default:
		break;
	}


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
			CheckNextPhaseX();
		}
	}
}
void GameScene::GameOver()
{
	finished_ = true;
}

void GameScene::GameClear()
{
	finished_ = true;
}

void GameScene::CheckNextPhaseO()
{
	// 現在のフェーズに応じた判定
	if (phase_ == GamePhase::Complete) {
		return;  // 完了フェーズなので何もしない
	}

	NextPhaseFlag = true;
	NextPhaseTimer = 180;

	ResetPosition();
	
	if (phase_==GamePhase::Phase1)
	{
		if (state_ == EnemyState::O)
		{
			phase_ = GamePhase::Phase2;
		}
	}

	if (phase_ == GamePhase::Phase2)
	{
		if (state_ == EnemyState::X)
		{
			++missCount_;
		}
	}

	if (phase_ == GamePhase::Phase3)
	{
		if (state_ == EnemyState::O)
		{
			phase_ = GamePhase::Phase4;
		}
	}

	if (phase_ == GamePhase::Phase4)
	{
		if (state_ == EnemyState::X)
		{
			++missCount_;
		}
	}

	if (phase_ == GamePhase::Phase5)
	{
		if (state_ == EnemyState::O)
		{
			phase_ = GamePhase::Complete;
		}
	}

	// 体力1減ったら
	if (missCount_ >= 1) {
		Health1Flag = true;
	}
	// 体力2減ったら
	if (missCount_ >= 2) {
		Health2Flag = true;
	}

	if (missCount_ >= 3) {
		Health3Flag = true;
		// 3回ミスでゲームオーバー
		GameOver();
	}

	if (phase_ == GamePhase::Complete) {
		GameClear();
	}
}

void GameScene::CheckNextPhaseX()
{
	// 現在のフェーズに応じた判定
	if (phase_ == GamePhase::Complete) {
		return;  // 完了フェーズなので何もしない
	}

	ResetPosition();

	if (phase_==GamePhase::Phase1)
	{
		if (state_ == EnemyState::O)
		{
			++missCount_;
		}
	}

	if (phase_ == GamePhase::Phase2)
	{
		if (state_ == EnemyState::X)
		{
			phase_ = GamePhase::Phase3;
		}
	}

	if (phase_ == GamePhase::Phase3)
	{
		if (state_ == EnemyState::O)
		{
			++missCount_;
		}
	}

	if (phase_ == GamePhase::Phase4)
	{
		if (state_ == EnemyState::X)
		{
			phase_ = GamePhase::Phase5;
		}
	}

	if (phase_ == GamePhase::Phase5)
	{
		if (state_ == EnemyState::O)
		{
			++missCount_;
		}
	}

	// 体力1減ったら
	if (missCount_ >= 1) {
		Health1Flag = true;
	}
	// 体力2減ったら
	if (missCount_ >= 2) {
		Health2Flag = true;
	}

	if (missCount_ >= 3) {
		Health3Flag = true;
		// 3回ミスでゲームオーバー
		GameOver();
	}

	if (phase_ == GamePhase::Complete) {
		GameClear();
	}
}

void GameScene::ResetPosition()
{
		// プレイヤーの初期位置を設定
		player_->SetPosition({ 0.0f, 1.0f, 0.0f });  // 初期位置の座標に変更

		enemy_->Revive();
		enemy2_->Revive();

		enemy_->Update();
		enemy2_->Update();
}
#pragma endregion