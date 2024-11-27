#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>
#include <algorithm>
#include <numbers>

Player::~Player()
{
	// bullet_の解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

	bullets_.clear();
}

void Player::Initialize(Model* model, ViewProjection* viewProjection){

	// NULLチェック
	assert(model);


	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	//textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.rotation_.y = std::numbers::pi_v<float>;

}

void Player::Update(){

	// ワールド行列の計算
	//worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();

	// 定数バッファに転送する
	worldTransform_.TransferMatrix();

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 画面範囲内に収まるように制限
	const float kLimitX = 35.0f;    // x軸の範囲
	const float kLimitY = -20.0f;    // y軸は下半分の範囲を設定
	const float kLimitZ = 10.0f;    // z軸の範囲

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kLimitX, kLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, kLimitY, 0.0f);
	worldTransform_.translation_.z = std::clamp(worldTransform_.translation_.z, -kLimitZ, kLimitZ);

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}


	
}

void Player::Draw(){

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(*viewProjection_);
	}
}

void Player::Rotate()
{
	//// 回転速さ
	//const float kRotSpeed = 0.02f;

	//// 押した方向で移動ベクトルを変更
	//if (input_->PushKey(DIK_A)) {
	//	worldTransform_.rotation_.y += kRotSpeed;
	//}else if (input_->PushKey(DIK_D)) {
	//	worldTransform_.rotation_.y -= kRotSpeed;
	//}
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);


		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}

void Player::SetPosition(const Vector3& position)
{
	worldTransform_.translation_ = position;
}


