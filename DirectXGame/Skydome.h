#pragma once
#include <WorldTransform.h>
#include <Model.h>

class Skydome
{
public:
	void Initalize(Model*model,ViewProjection*viewProjection);

	void Update();

	void Draw();
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
};

