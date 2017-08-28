#include "Engine.h"
#include "graphics/EffectManager.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		GetEngine().Release();
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Engine::Engine()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

Engine::~Engine()
{
}


void Engine::InitD3D(HINSTANCE& hInst)
{

	UNREFERENCED_PARAMETER(hInst);
	//�E�B���h�E�N���X���쐬
	m_wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,0L,0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"Game", NULL
	};
	//�E�B���h�E�N���X��o�^
	RegisterClassEx(&m_wc);

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow("Game", "Game",
		WS_OVERLAPPEDWINDOW, 50, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT,
		NULL, NULL, m_wc.hInstance, NULL);

	//D3D�I�u�W�F�N�g���쐬����
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//D3D�f�o�C�X���쐬���邽�߂̃p�����[�^��ݒ肷��B
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//D3D�f�o�C�X���쐬����B
	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice);
	if (hr == D3DERR_INVALIDCALL)
	{
		std::abort();
	}
	m_effectManager = new EffectManager;

	// show the window
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

void Engine::GameLoop()
{
	//�Q�[�����[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_objectManager.Execute(m_pD3DDevice);
		}
	}

	UnregisterClass("shader Tutorial", m_wc.hInstance);
}