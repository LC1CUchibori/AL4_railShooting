#include "RailCamera.h"
#include <imgui.h>
#include <MyMath.h>

void RailCamera::Initialize(const Vector3& position, const Vector3& rotationRadians)
{
	// ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotationRadians;
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// 移動
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);
	// 回転
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	viewProjection_.TransferMatrix();

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Position", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
};
