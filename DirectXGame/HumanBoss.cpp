#include "HumanBoss.h"
#include <cassert>
#include <numbers>
#include <cmath>

auto easeInBack(float x){
	const float c1 = 1.70158f;
	const float c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}

auto easeInOutCubic(float x) {
	return x < 0.5f ? 4.0f * x * x * x : 1 - std::pow(-2.0f * x + 2.0f, 3.0f) / 2.0f;
}

// グローバル or クラス内で乱数エンジンを準備
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> randomDisplacement(-0.02f, 0.02f); // -0.01～0.01の範囲



void HumanBoss::Initialize(Model *model, ViewProjection* viewProjection/*, const Vector3& position*/) { 

	// NULLポインタチェック
	assert(model);

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.scale_ = {11.0f,10.0f,10.0f};
	worldTransform_.rotation_.y = std::numbers::pi_v<float>;
	worldTransform_.translation_={0.0f,25.0f,80.0f};

}

void HumanBoss::Update() {
	worldTransform_.UpdateMatrix();

	if (!action) {
		isMove = 1;      //フラグを1にする
		action=true;
		startframe = 0;       //frameを0に
	}
	if (isMove == 1) {
		startframe++;         //フラグが1の時にフレームを＋し続ける
		worldTransform_.rotation_.y+=0.1*std::numbers::pi_v<float>;
	}
	if (startframe == endframe) {
		isMove = 0;      //frameがendframeと同じになったらフラグを0にする
	}

	x = startframe / endframe;//現在の時間÷全体の時間

	worldTransform_.translation_.z = start + (end - start) * easeInBack(x);

	// `frame` を整数型に変更
	static int frame = 0; // フレーム数は整数型で管理
	frame++; // フレームを加算

	if (action) {
		// 中心位置を基準に動かす
		const float centerX = 0.0f;  // 中心X座標
		const float centerY = 25.0f; // 中心Y座標

		// 動く範囲の制限（振幅を小さくする）
		const float amplitudeX = 5.0f; // X軸の揺れの範囲
		const float amplitudeY = 4.0f; // Y軸の揺れの範囲

		// サイン波とランダム変位を加えて範囲内で動くようにする
		worldTransform_.translation_.x = centerX + sin(frame * 0.02f) * amplitudeX + randomDisplacement(mt);
		worldTransform_.translation_.y = centerY + cos(frame * 0.015f) * amplitudeY + randomDisplacement(mt);
	}

}

void HumanBoss::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}