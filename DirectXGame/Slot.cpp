#include "Slot.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

void Slot::Initialize()
{
	// NULL�`�F�b�N
	assert(model);

	// 3D���f���̐���
	model_ = Model::Create();
	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
}

void Slot::Update()
{
}

void Slot::Draw()
{
	model_->Draw();
}
