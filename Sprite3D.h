#pragma once
//#DirectX�̂��
#include"ErrorException.h"

//����.h
#include"DX12Math.h"
#include"WinApi.h"
#include"DirectXCore.h"
#include "Camera.h"
#include"SpriteInterface.h"
//pragma comment



//using namespace


class Sprite3D : public SpriteInterface
{
private:


public:

	Sprite3D() = default;
	~Sprite3D() = default;

	//������
	virtual void Initialize(ModelShareVaria& modelShareVaria);

	///<summary>
	///�ǂݍ���
	///</summary>
	///<param name="filePath">�t�@�C���p�X</param>
	virtual void Load(const wchar_t* filePath);

	///<summary>
	///�X�V
	///</summary>
	///<param name="pos">���W</param>
	///<param name="rot">��]</param>
	///<param name="scale">�g�嗦</param>
	/// ///<param name="color"> �J���[</param>
	virtual void Update(const DX12Math::Vector3& pos = { 0.0f, 0.0f, 0.0f }, const DX12Math::Vector3& rot = { 0.0f, 0.0f, 0.0f }, const DX12Math::Vector3& scale = { 1.0f,1.0f, 1.0f }, const DX12Math::Vector4& color = { 1.0f,1.0f, 1.0f, 1.0f });

	///<summary>
	///�`��
	///</summary>
	virtual void Draw(Camera*& camera)
		;
private:

	//�V�F�[�_�|���\�[�X�r���[����
	virtual void CreateShaderResourceView();
	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	virtual void CreatConstBuff();
	//���_�o�b�t�@�E�C���f�b�N�X����
	virtual void CreatVertexIndexBuffer();
	//�e�N�X�`���o�b�t�@����
	virtual void CreatTextureBuffer();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Sprite3D& operator=(const Sprite3D&) = delete;
	Sprite3D(const Sprite3D&) = delete;
};

