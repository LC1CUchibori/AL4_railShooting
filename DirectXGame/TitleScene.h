#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GameScene.h"
/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene {
public:
    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// ���t���[������
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    bool IsFinished() const { return finished_; }

private:

    DirectXCommon* dxCommon_ = nullptr;
    WorldTransform titleWorldTransform_;
    ViewProjection viewProjection_;

    bool finished_ = false;

    uint32_t TitleHandle_ = 0;
    Sprite* titleSprite_ = nullptr;
};