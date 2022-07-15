#pragma once
#include "ErrorException.h"

#include "DirectXCore.h"
#include "WinApi.h"
#include "DX12Math.h"

#pragma comment(lib, "d3dcompiler.lib")

// ���W�E�J���[
struct PosColor
{
	DX12Math::Vector3 pos; // ���W
	DX12Math::Vector4 color; // �J���[
};

// �p�C�v���C���E���[�g�V�O�l�`���Z�b�g
struct PipelineSet
{
	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

//�o�b�t�@�֘A
struct Buff
{
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//���_�}�b�v
	PosColor* vertMap;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuff;
	////�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap;
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
};

//�u�����h���[�h
enum class BlendMode
{
	BLENDMODE_NOBLEND,//�m�[�u�����h�i�f�t�H���g�j
	BLENDMODE_ALPHA,//���u�����h
	BLENDMODE_ADD,//���Z�u�����h
	BLENDMODE_SUB,//���Z�u�����h
	BLENDMODE_MULA,//��Z�u�����h
	BLENDMODE_INVSRC,//���]�u�����h

	BLENDMODE_MAX//�u�����h��ސ�
};

class Mesh
{
public:
	// �R���X�g���N�^
	Mesh();

	///<summary>
	///�u�����h���[�h��ݒ肷��
	///</summary>
	///<param name="mode">: �u�����h���[�h</param>
	void SetBlendMode(BlendMode mode);

	///<summary>
	///�F�R�[�h���擾����
	///</summary>
	///<param name="red">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="blue">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="green">: �擾�������F�̋P�x�l : �����l255 (0�`255)</param>
	///<param name="alpha">: �擾�������F�̓��ߗ� : �����l255 (0�`255)</param>
	///<returns>�F�R�[�h</returns>
	DX12Math::Vector4 GetColor(int red = 255, int blue = 255, int green = 255, int alpha = 255);

private:
	DirectXCore* directXCore = nullptr;

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�萔�o�b�t�@�̃}�b�s���O�p�|�C���^
	ConstBufferDataTransform* constMapTransform = nullptr;

	//�u�����h���[�h
	UINT blendMode;
	char PADDING[4];

	//�p�C�v���C���쐬
	std::unique_ptr < PipelineSet> CreatPipeline(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode);

	///<summary>
	///�o�b�t�@�쐬
	///</summary>
	///<param name="vertexCount">: ���_��</param>
	///<param name="indexCount">: �C���f�b�N�X��</param>
	///<returns>�o�b�t�@</returns>
	std::unique_ptr <Buff> CreateBuff(UINT vertexCount, UINT indexCount);

	//�e��p�C�v���C���Z�b�g����
	void CreatArryPipeline();

	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	void CreatConstBuff();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Mesh& operator=(const Mesh&) = delete;
	Mesh(const Mesh&) = delete;
};

