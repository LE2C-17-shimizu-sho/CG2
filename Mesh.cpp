#include "Mesh.h"

#pragma region �p�u���b�N

//�R���X�g���N�^
Mesh::Mesh()
{
	directXCore = DirectXCore::GetInstance();

	//�e��p�C�v���C������
	CreatArryPipeline();

	////�O�p�`�o�b�t�@
	//UINT vertexCount = triangleVertexCount * triangleMaxCount;
	//UINT indexCount = triangleIndexCount * triangleMaxCount;
	//triangleBuff = CreateBuff(vertexCount, indexCount);

	////���o�b�t�@
	//vertexCount = lineVertexCount * lineMaxCount;
	//indexCount = lineIndexCount * lineMaxCount;
	//lineBuff = CreateBuff(vertexCount, indexCount);

	////�l�p�`�o�b�t�@
	//vertexCount = boxVertexCount * boxMaxCount;
	//indexCount = boxIndexCount * boxMaxCount;
	//boxBuff = CreateBuff(vertexCount, indexCount);

	CreatConstBuff();

}

//�u�����h���[�h��ݒ肷��
void Mesh::SetBlendMode(BlendMode mode)
{
	blendMode = (UINT)mode;
}

//�F�R�[�h���擾����
DX12Math::Vector4 Mesh::GetColor(int red, int blue, int green, int alpha)
{
	DX12Math::Vector4 color{};

	color.x = static_cast<float>(red) / 255.0f;
	color.y = static_cast<float>(blue) / 255.0f;
	color.z = static_cast<float>(green) / 255.0f;
	color.w = static_cast<float>(alpha) / 255.0f;

	return color;
}
#pragma endregion

#pragma region �v���C�x�[�g
//�萔�o�b�t�@����(2D���W�ϊ��s��)
void Mesh::CreatConstBuff()
{
	//�萔�o�b�t�@����
	directXCore->CreateConstBuff(constMapTransform, constBuffTransform);

	DX12Math::MakeOrthogonalL(
		0.0f, static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_width),
		static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_height), 0.0f,
		0.0f, 1.0f, constMapTransform->mat);

}