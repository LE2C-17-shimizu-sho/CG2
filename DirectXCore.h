#pragma once
#include "ErrorException.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class DirectXCore
{
private:

	//�R���X�g���N�^�E�f�X�g���N�^
	DirectXCore() = default;
	~DirectXCore() = default;

	// DirectX ����������
	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;


	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	// �[�x�e�X�g�̐ݒ�
	ID3D12Resource* depthBuff = nullptr;
	ID3D12DescriptorHeap* dsvHeap = nullptr;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	// �o�b�N�o�b�t�@
	std::vector<ID3D12Resource*> backBuffers;

	// �t�F���X�̐���
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;

	//�r���[�|�[�g
	D3D12_VIEWPORT viewport{};

	//�V�U�[��`
	D3D12_RECT scissorRect{};

	//�o���A�[�f�X�N
	D3D12_RESOURCE_BARRIER barrierDesc{};

	FLOAT clearColor[4] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ΐF


	//DXGI�܂�菉����
	HRESULT InitializeDXGI();

	//�ŏI�I�ȃ����_�[�^�[�Q�b�g�̐���
	HRESULT CreatRtv();

	//�X���b�v�`�F�C���̐���
	HRESULT CreateSwapChain();

	//�[�x�e�X�g
	HRESULT CreateDepthHeap();

	//�R�}���h�܂�菉����
	HRESULT InitializeCommand();

	//�t�F���X����
	HRESULT CreateFence();

	//�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer();


public:
	static DirectXCore* GetInstance();

	// DirectX���t���[��������������
	void InitializeDirectXCore();
	void DrawStart();
	void DrawEnd();
	void ExecuteCommand();
	// DirectX���t���[�����������܂�

	// �Z�b�^�[
	//�w�i�F�ύX(RGBA)
	void SetBackScreenColor(float red, float green, float blue, float alpha);

	// �Q�b�^�[
	ID3D12Device* GetDevice();
	IDXGIFactory7* GetDxgiFactory();
	IDXGISwapChain4* GetSwapChain();
	ID3D12CommandAllocator* GetCmdAllocator();
	ID3D12GraphicsCommandList* GetCommandList();
	ID3D12CommandQueue* GetCommandQueue();
	ID3D12DescriptorHeap* GetRtvHeap();
	ID3D12Fence* GetFence();
	UINT64 GetFenceVal();

#pragma region �e���v���[�g�֐�
	//�萔�o�b�t�@�쐬
	template<typename T>
	void CreateConstBuff(T*& buff, Microsoft::WRL::ComPtr<ID3D12Resource>& constBuff)
	{

		// ���_�o�b�t�@�̐ݒ�
		D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
		// ���\�[�X�ݒ�
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Width = (sizeof(T) + 0xff) & ~0xff; // ���_�f�[�^�S�̂̃T�C�Y
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//�萔�o�b�t�@�̐���
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̃}�b�s���O
		result = constBuff->Map(0, nullptr, (void**)&buff);//�}�b�s���O
		assert(SUCCEEDED(result));

	}
};
