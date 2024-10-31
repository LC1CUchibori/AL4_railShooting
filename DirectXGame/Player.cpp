#include "Player.h"
#include <cassert>
#include <ImGuiManager.h>

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection){

	// NULLチェック
	assert(model);


	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

}

void Player::Update(){

	// ワールド行列の計算
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 定数バッファに転送する
	worldTransform_.TransferMatrix();

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	ImGui::Begin("Player");
	ImGui::SliderFloat3("Position",&worldTransform_.translation_.x,-10.0f,10.0f);
	ImGui::End();
}

void Player::Draw(){

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}
