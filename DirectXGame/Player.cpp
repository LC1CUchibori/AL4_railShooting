#include "Player.h"
#include <cassert>

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

	// ワールドトランスフォームブロックの初期化
	worldTransformBlock_->scale = { 1.0f, 1.0f, 1.0f };
	worldTransformBlock_->rotation = { 0.0f, 0.0f, 0.0f };
	worldTransformBlock_->translation = { 0.0f, 0.0f, 0.0f };

	// ワールド行列の計算
	worldTransformBlock_->matWorld = MakeAffineMatrix(worldTransformBlock_->scale, worldTransformBlock_->rotation, worldTransformBlock_->translation);

	// 定数バッファに転送する
	worldTransformBlock_->TransferMatrix();

	// 行列を定数バッファに転送
	//worldTransform_.TransferMatrix();

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
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y += kCharacterSpeed;
	}

	// 座標移動(ベクトルの加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
}

void Player::Draw(){

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}

void WorldTransformBlock::TransferMatrix()
{
}
