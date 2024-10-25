#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"
#include "MyMath.h"

class WorldTransformBlock
{
public:

	Matrix4x4 matWorld;  // ワールド行列
	Vector3 scale;          // スケール
	Vector3 rotation;       // 回転
	Vector3 translation;    // 平行移動
	void TransferMatrix();

private:

};

