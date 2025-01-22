#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include "GameScene.h"

class RailCamera
{
public:
	void Initialize(const Vector3& position, const Vector3& rotationRadians);
	
	void Update();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
};

