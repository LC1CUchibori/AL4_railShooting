#pragma once
#include <WorldTransform.h>
#include <Model.h>
#include "DirectXCommon.h"

class Skydome
{
public:
	void Initalize();

	void Update();

	void Draw();
private:
	DirectXCommon* dxCommon_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	// モデル
	//Model* model_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;
	// 3Dモデル
	Model* modelSkydome_ = nullptr;
};

