#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <dinput.h>
#include <array>

class Input {
public:
	Input() = default;
	~Input() = default;
	void Initialize(HRESULT result, HWND hwnd, WNDCLASSEX w);
	void Update();
	bool PushKey(uint8_t index);
	bool ReleaseKey(uint8_t index);
	bool TriggerPushKey(uint8_t index);
	bool TriggerReleaseKey(uint8_t index);
	
private:

	//�L�[�{�[�h�f�o�C�X
	IDirectInput8* directInput = nullptr;
	IDirectInputDevice8* keyboard = nullptr;

	BYTE oldkey[256] = {};
	BYTE key[256] = {};
};