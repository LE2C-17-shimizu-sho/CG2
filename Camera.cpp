#include "Camera.h"

void Camera::Initialize(UpdateProMatFunc matFunc)
{
	// �A�X�y�N�g����v�Z����
	aspect =
		static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_width) /
		static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_height);

	matrixFunc = matFunc;

	if (matFunc == UpdateProMatFunc_Ortho)
	{
		if (far_ = 0.0f)
		{
			far_ = 1.0f;
		}
		right = static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_width);
		bottom = static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_height);

		// ���s���e�̌v�Z
		DX12Math::MakeOrthogonalL(left, right, bottom, top, near_, far_, proMatrix);
	}
	else// �������e
	{
		if (near_ == 0.0f)
		{
			near_ = 0.1f;
		}
		if (far_ == 0.0f)
		{
			far_ = 1000.0f;
		}
		if (fovAngleY == 0.0f)
		{
			fovAngleY = DX12Math::AX_PIF / 4;
		}

		//�������e�s��̌v�Z
		DX12Math::MakePerspectiveL(fovAngleY, aspect, near_, far_, proMatrix);
	}
	//�r���[�s��̍X�V�t���O
	updateProMatrix = false;

	// �r���[�s��̎Z�o
	DX12Math::MakeLookL(eye, target, up, viewMatrix);
	// �r���[�s��̋t�s����v�Z
	viewMatrixInv = DX12Math::MakeInverse(viewMatrix);
	// �r���[�v���W�F�N�V�����s��̍쐬
	viewProMatrix = viewMatrix * proMatrix;

	// �J�����̑O�x�N�g���擾
	forward = { viewMatrixInv.m[2][0],viewMatrixInv.m[2][1] ,viewMatrixInv.m[2][2] };
	forward.normalization();

	// �����_�Ǝ��_�̋����擾
	DX12Math::Vector3 toPos;
	toPos = eye - target;
	tgtToPosLen = toPos.length();

	//�r���[�s��̍X�V�t���O
	updateViewMatrix = false;
}

void Camera::Update()
{
	if (updateProMatrix)
	{
		if (matrixFunc == UpdateProMatFunc_Ortho)
		{
			if (far_ == 0.0f)
			{
				far_ = 1.0f;
			}

			right = static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_width);
			bottom = static_cast<float>(WinApi::GetInstance()->GetWindowSize().window_height);
			DX12Math::MakeOrthogonalL(left, right, bottom, top, near_, far_, proMatrix);
		}
		else
		{
			if (near_ == 0.0f)
			{
				near_ = 0.1f;
			}
			if (far_ == 0.0f)
			{
				far_ = 1000.0f;
			}
			if (fovAngleY == 0.0f)
			{
				fovAngleY = DX12Math::AX_PIF / 4;
			}

			DX12Math::MakePerspectiveL(fovAngleY, aspect, near_, far_, proMatrix);
		}
		updateProMatrix = false;
	}

	if (updateViewMatrix)
	{
		// �r���[�s��̎Z�o
		DX12Math::MakeLookL(eye, target, up, viewMatrix);
		// �r���[�v���W�F�N�V�����s��̍쐬
		viewProMatrix = viewMatrix * proMatrix;
		// �r���[�s��̋t�s����v�Z
		viewMatrixInv = DX12Math::MakeInverse(viewMatrix);

		forward = { viewMatrixInv.m[2][0],viewMatrixInv.m[2][1],viewMatrixInv.m[2][2] };

		DX12Math::Vector3 toPos;
		toPos = eye - target;
		tgtToPosLen = toPos.length();

		updateViewMatrix = false;
	}
}

void Camera::Move(const DX12Math::Vector3& move)
{
	eye += move;
	target += move;
	updateViewMatrix = true;
}

void Camera::MoveTarget(const DX12Math::Vector3& move)
{
	target += move;
	updateViewMatrix = true;
}

void Camera:: MovePos(const DX12Math::Vector3& move)
{
	eye += move;
	updateViewMatrix = true;
}

#pragma region �Z�b�^�[
void Camera::SetAspect(float aspect_)
{
	aspect = aspect_;
	updateViewMatrix = true;
}

void Camera::SetPos(const DX12Math::Vector3& pos)
{
	eye = pos;
	updateViewMatrix = true;
}

void Camera::SetPos(float x, float y, float z)
{
	SetPos(DX12Math::Vector3(x, y, z));
}

void Camera::SetTarget(const DX12Math::Vector3& tgt)
{
	target = tgt;
	updateViewMatrix = true;
}

void Camera::SetTarget(float x, float y, float z)
{
	SetTarget(DX12Math::Vector3(x, y, z));
}

void Camera::SetUp(const DX12Math::Vector3& upVec)
{
	up = upVec;
	up.normalization();
	updateProMatrix = true;
}

void Camera::SetUp(float x, float y, float z)
{
	SetUp(DX12Math::Vector3(x, y, z));
}

void Camera::SetFar(float fFar)
{
	far_ = fFar;
	updateProMatrix = true;
}

void Camera::SetNear(float fNear)
{
	near_ = fNear;
	updateProMatrix = true;
}

void Camera::SetFovAngleY(float fovAngle)
{
	this->fovAngleY = fovAngle;
	updateProMatrix = true;
}

void Camera::SetUpdateProMatrixFunc(UpdateProMatFunc func)
{
	matrixFunc = func;
	updateProMatrix = true;
}

void Camera::SetLeft(float left_)
{
	left = left_;
	updateProMatrix = true;
}
void Camera::SetRight(float right_)
{
	right = right_;
	updateProMatrix = true;
}

void Camera::SetTop(float top_)
{
	top = top_;
	updateProMatrix = true;
}

void Camera::SetBottom(float bottom_)
{
	bottom = bottom_;
	updateProMatrix = true;
}

#pragma endregion

#pragma region �Q�b�^�[
const DX12Math::Vector3& Camera::GetPos() const
{
	return eye;
}

const DX12Math::Vector3& Camera::GetTarget() const
{
	return target;
}

const DX12Math::Vector3& Camera::GetUp() const
{
	return up;
}

const DX12Math::Matrix4& Camera::GetViewMatrix()
{
	//�X�V
	Update();
	return viewMatrix;
}

const DX12Math::Matrix4& Camera::GetViewMatrixInv()
{
	//�X�V
	Update();
	return viewMatrixInv;
}

const DX12Math::Matrix4& Camera::GetProjectionMatrix()
{
	//�X�V
	Update();
	return proMatrix;
}

const DX12Math::Matrix4& Camera::GetViewProjectionMatrix()
{
	//�X�V
	Update();
	return viewProMatrix;
}

const DX12Math::Matrix4& Camera::GetCameraRotation()
{
	//�X�V
	Update();
	return cameraRot;
}

float Camera::GetFar() const
{
	return far_;
}

float Camera::GetNear() const
{
	return near_;
}

float Camera::GetFovAngleY() const
{
	return fovAngleY;
}

float Camera::GetTargetToPositionLength() const
{
	return tgtToPosLen;
}

const DX12Math::Vector3& Camera::GetForward() const
{
	return forward;
}

float Camera::GetAspect() const
{
	return aspect;
}

float Camera::GetLeft()
{
	return left;
}

float Camera::GetRight()
{
	return right;
}

float Camera::GetTop()
{
	return top;
}

float Camera::GetBottom()
{
	return bottom;
}
#pragma endregion