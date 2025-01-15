#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include "GameScene.h"

class RailCamera
{
public:
	void Initialize(const Vector3& position, float rotationRadians);
	
	void Update();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
};

