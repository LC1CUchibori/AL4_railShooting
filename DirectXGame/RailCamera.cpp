#include "RailCamera.h"
#include <imgui.h>

void RailCamera::Initialize(const Vector3& position, float rotationRadians)
{
	// ワールドトランスフォームの初期化
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ .x= rotationRadians;
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// 移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
	// 回転
	worldTransform_.rotation_.x += move.x;
	worldTransform_.rotation_.y += move.y;
	worldTransform_.rotation_.z += move.z;

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Position",&worldTransform_.translation_.x,-10.0f,10.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();
}
