#pragma once

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

    void Initialize();

    void Update();

    void Draw();

private:
    DirectXCommon* dxCommon = nullptr;
    Input* input = nullptr;
    Audio* audio = nullptr;

    // 3D���f��
    Model* model = nullptr;
    // ���[���h�g�����X�t�H�[��
    WorldTransform worldTransform;
    // �r���[�v���W�F�N�V����
    ViewProjection viewProjection;
};