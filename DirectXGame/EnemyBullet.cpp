//#include "EnemyBullet.h"
//#include <cassert>
//
//void EnemyBullet::Initialize(Model* model, const Vector3& position)
//{
//	// NULLポインタチェック
//	assert(model);
//
//	model_ = model;
//	// テクスチャ読み込み
//	textureHandle_ = TextureManager::Load("white1x1.png");
//	// ワールドトランスフォームの初期化
//	worldTransform_.Initialize();
//
//	worldTransform_.translation_ = position;
//}
//
//void EnemyBullet::Update()
//{
//	// 座標を移動させる
//	worldTransform_.translation_.z += 2.0f;
//
//	if (--deathTimer_ <= 0) {
//		isDead_ = true;
//	}
//
//	// 行列を更新
//	worldTransform_.UpdateMatrix();
//}
//
//void EnemyBullet::Draw(const ViewProjection& viewProjection)
//{
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//}
