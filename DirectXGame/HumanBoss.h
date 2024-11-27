#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Viewprojection.h"
#include <random>

class HumanBoss
{
public:
	void Initialize(Model* model, ViewProjection* viewProjection/*, const Vector3& position*/); 

	void Update();

	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* model_ = nullptr;

	float posX = 0;
	double posx = 0;
	float start = 90, end = 75;
	float startframe = 0, endframe = 60;

	int isMove = 0;
	bool action=false;

	float x = 100;

};