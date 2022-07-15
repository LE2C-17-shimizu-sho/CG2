#pragma once
#include "DX12Math.h"
#include "WinApi.h"

enum UpdateProMatFunc
{
	UpdateProMatFunc_Perspective,	// �����ˉe�s��
	UpdateProMatFunc_Ortho,			// ���s���e
};

class Camera
{
private:

	// �r���[�s��
	DX12Math::Matrix4 viewMatrix;
	// �v���W�F�N�V�����s��
	DX12Math::Matrix4 proMatrix;
	// �r���[�v���W�F�N�V�����s��
	DX12Math::Matrix4 viewProMatrix;
	// �r���[�s��̋t�s��
	DX12Math::Matrix4 viewMatrixInv;
	// �J�����̉�]�s��
	DX12Math::Matrix4 cameraRot;

	// ���_���W
	DX12Math::Vector3 eye = { 0.0f,0.0f,-100.0f };
	// �����_���W
	DX12Math::Vector3 target = { 0.0f,0.0f,0.0f };
	// ������x�N�g��
	DX12Math::Vector3 up = { 0.0f,1.0f,0.0f };

	// ��p(���W�A���x)
	float fovAngleY = 0.0f;
	// �A�X�y�N�g��(��ʉ���/��ʏc��)
	float aspect = 0.0f;
	// �j�A�N���b�v(�O�[)
	float near_ = 0.0f;
	// �t�@�[�N���b�v(���[)
	float far_ = 0.0f;
	// ��ʍ���
	float left = 0.0f;
	// ��ʉE��
	float right = 0.0f;
	// ��ʏ㑤
	float top = 0.0f;
	// ��ʉ���
	float bottom = 0.0f;

	// �v���W�F�N�V�����s��̍X�V�t���O
	bool updateProMatrix = true;
	// �r���[�s��̍X�V�t���O
	bool updateViewMatrix = true;
	char PADDING[2]{};

	// �����_�Ǝ��_�̋���
	float tgtToPosLen = 0.0f;

	// �J�����̐��ʃx�N�g��
	DX12Math::Vector3 forward = { 0.0f,0.0f,0.0f };

	UpdateProMatFunc matrixFunc = UpdateProMatFunc_Perspective;

public:

	// �R���X�g���N�^�E�f�X�g���N�^
	Camera() = default;
	~Camera() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="matFunc">�����ˉeor���s���e</param>
	void Initialize(UpdateProMatFunc matFunc);

	/// <summary>
	/// �r���[�s��E�v���W�F�N�V�����s����X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �J�����𓮂���
	/// </summary>
	/// <param name="move">��������</param>
	void Move(const DX12Math::Vector3& move);

	/// <summary>
	/// �����_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MoveTarget(const DX12Math::Vector3& move);

	/// <summary>
	/// ���_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MovePos(const DX12Math::Vector3& move);

#pragma region �Z�b�^�[

	/// <summary>
	/// �A�X�y�N�g���ݒ肷��
	/// </summary>
	/// <param name="aspect_">�A�X�y�N�g��</param>
	void SetAspect(float aspect_);

	/// <summary>
	/// �J�����̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos"> : �ݒ肵�������W</param>
	void SetPos(const DX12Math::Vector3& pos);

	/// <summary>
	/// �J�����̍��W���Œ肷��
	/// </summary>
	/// <param name="x,y,z"> : �J�����̍��W��ݒ�</param>
	void SetPos(float x, float y, float z);


	/// <summary>
	/// �����_��ݒ�
	/// </summary>
	/// <param name="target"> : �ݒ肵�����^�[�Q�b�g�̍��W</param>
	void SetTarget(const DX12Math::Vector3& target);

	/// <summary>
	/// �����_��ݒ�
	/// </summary>
	/// <param name="x,y,z"> : �ݒ肵�������W</param>
	void SetTarget(float x, float y, float z);

	/// <summary>
	/// �J�����̏������ݒ�
	/// </summary>
	void SetUp(const DX12Math::Vector3& upVec);

	/// <summary>
	/// �J�����̏������ݒ�
	/// </summary>
	void SetUp(float x, float y, float z);

	/// <summary>
	/// �����ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetFar(float fFar);

	/// <summary>
	/// �ߕ��ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetNear(float fNear);

	/// <summary>
	/// �s��̌v�Z���@��ݒ�
	/// </summary>
	/// <param name="func"></param>
	void SetUpdateProMatrixFunc(UpdateProMatFunc func);

	/// <summary>
	/// ��p��ݒ�
	/// </summary>
	/// <remarks>
	/// SetUpdateProjMatrixFunc��enUpdateProjMatrixFunc_Perspective���ݒ肳��Ă���Ƃ��Ɏg�p�����B
	/// </remarks>
	/// <param name="viewAngle">��p�B�P�ʃ��W�A��</param>
	void SetFovAngleY(float fovAngle);

	/// <summary>
	/// ���s���e�̍��[��ݒ�
	/// </summary>
	/// <param name="left_">���[</param>
	void SetLeft(float left_);

	/// <summary>
	/// ���s���e�̉E�[��ݒ�
	/// </summary>
	/// <param name="right_">�E�[</param>
	void SetRight(float right_);

	/// <summary>
	/// ���s���e�̏�[��ݒ�
	/// </summary>
	/// <param name="top_">��[</param>
	void SetTop(float top_);

	/// <summary>
	/// ���s���e�̉��[��ݒ�
	/// </summary>
	/// <param name="bottom_">���[</param>
	void SetBottom(float bottom_);
#pragma endregion

#pragma region �Q�b�^�[

	/// <summary>
	/// �����_���擾
	/// </summary>
	const DX12Math::Vector3& GetTarget() const;

	/// <summary>
	/// �J�����̍��W���擾
	/// </summary>
	const DX12Math::Vector3& GetPos() const;

	/// <summary>
	/// �J�����̏�������擾
	/// </summary>
	const DX12Math::Vector3& GetUp() const;

	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	const DX12Math::Matrix4& GetViewMatrix();

	/// <summary>
	/// �r���[�s��̋t�s����擾
	/// </summary>
	const DX12Math::Matrix4& GetViewMatrixInv();

	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	const DX12Math::Matrix4& GetProjectionMatrix();

	/// <summary>
	/// �r���[�~�v���W�F�N�V�����s����擾
	/// </summary>
	const DX12Math::Matrix4& GetViewProjectionMatrix();

	/// <summary>
	/// �J�����̉�]�s����擾
	/// </summary>
	const DX12Math::Matrix4& GetCameraRotation();

	/// <summary>
	/// �����ʂ܂ł̋������擾
	/// </summary>
	float GetFar() const;

	/// <summary>
	/// �ߕ��ʂ܂ł̋������擾
	/// </summary>
	float GetNear() const;

	/// <summary>
	/// �A�X�y�N�g����擾
	/// </summary>
	float GetAspect() const;

	/// <summary>
	/// ��p���擾
	/// </summary>
	/// <returns>��p�B�P�ʃ��W�A��</returns>
	float GetFovAngleY() const;

	/// <summary>
	/// �����_�Ǝ��_�̋������擾
	/// </summary>
	/// <returns></returns>
	float GetTargetToPositionLength() const;

	/// <summary>
	/// �J�����̑O�������擾
	/// </summary>
	const DX12Math::Vector3& GetForward() const;

	/// <summary>
	/// ���s���e�̉��[���擾
	/// </summary>
	float GetBottom();

	/// <summary>
	/// ���s���e�̏�[���擾
	/// </summary>
	float GetTop();

	/// <summary>
	/// ���s���e�̉E�[���擾
	/// </summary>
	float GetRight();

	/// <summary>
	/// ���s���e�̍��[���擾
	/// </summary>
	float GetLeft();

#pragma endregion
};

