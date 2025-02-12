#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Slot
{
public:
    Slot();

    ~Slot();

    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

private:
    DirectXCommon* dxCommon = nullptr;
    Input* input = nullptr;
    Audio* audio = nullptr;

    // 3Dモデル
    Model* model = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform;
    // ビュープロジェクション
    ViewProjection viewProjection;
};