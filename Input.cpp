#define DIRECTINPUT_VERSION 0x0800	//DirectInput�̃o�[�W�����w��
#include "Input.h"
#include <Windows.h>
#include <dinput.h>
#include "WinApi.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;

void Input::Initialize(HRESULT result, HWND hwnd, WNDCLASSEX w)//������
{
	//DirectInput�̏�����
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {
	// �S�L�[�̓��͏�Ԃ��擾����

	for (int i = 0; i < _countof(oldkey); i++)
	{
		oldkey[i] = key[i];
	}
	keyboard->Acquire();
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(uint8_t index) { // ���������
	return key[index];
}

bool Input::ReleaseKey(uint8_t index) { // ���������
	return !key[index] && !oldkey[index];
}

bool Input::TriggerPushKey(uint8_t index) { // �������u��
	return key[index] && !oldkey[index];
}

bool Input::TriggerReleaseKey(uint8_t index) { // �������u��
	return !key[index] && oldkey[index];
}