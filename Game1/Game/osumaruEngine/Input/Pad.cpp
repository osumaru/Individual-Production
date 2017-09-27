#include "engineStdafx.h"
#include "Pad.h"

const int triggerMax = 255;			//トリガーの入力値が0〜255なので正規化するときに使う

const float inputDeadZone = 0.2f;	//入力量の誤差の範囲

struct CorrespondencePad
{
	PadButton	padButton;
	DWORD		padCode;
	DWORD		keyCode;
};

const CorrespondencePad correspondencePad[padButtonNum] = 
{
	{ padButtonUp,			XINPUT_GAMEPAD_DPAD_UP,			'W' },
	{ padButtonDown,		XINPUT_GAMEPAD_DPAD_DOWN,		'S' },
	{ padButtonLeft,		XINPUT_GAMEPAD_DPAD_LEFT,		'A' },
	{ padButtonRight,		XINPUT_GAMEPAD_DPAD_RIGHT,		'D' },
	{ padButtonA,			XINPUT_GAMEPAD_A,				'J' },
	{ padButtonB,			XINPUT_GAMEPAD_B,				'K' },
	{ padButtonX,			XINPUT_GAMEPAD_X,				'I' },
	{ padButtonY,			XINPUT_GAMEPAD_Y,				'O' },
	{ padButtonStart,		XINPUT_GAMEPAD_START,			'B' },
	{ padButtonSelect,		XINPUT_GAMEPAD_BACK,			'V' },
	{ padButtonRB,			XINPUT_GAMEPAD_RIGHT_SHOULDER,	'2' },
	{ padButtonRStickPush,	XINPUT_GAMEPAD_RIGHT_THUMB,		'4' },
	{ padButtonLB,			XINPUT_GAMEPAD_LEFT_SHOULDER,	'7' },
	{ padButtonLStickPush,	XINPUT_GAMEPAD_LEFT_THUMB,		'9' }
};
Pad::Pad()
{
	m_padNum = 0;
	for (bool& isPad : m_isPadPress)
	{
		isPad = false;
	}
	for (bool& isPad : m_isPadTrigger)
	{
		isPad = false;
	}
	m_rightStickX = 0.0f;
	m_rightStickY = 0.0f;
	m_leftStickX = 0.0f; 
	m_leftStickY = 0.0f;
	m_rightTrigger = 0.0f;
	m_leftTrigger = 0.0f;
}

Pad::~Pad()
{

}

void Pad::Update()
{
	DWORD result = XInputGetState(m_padNum, &m_state);

	if (result == ERROR_SUCCESS)
	{
		for (const CorrespondencePad& pad : correspondencePad)
		{
			if (m_state.Gamepad.wButtons & pad.padCode)
			{
				if (!m_isPadPress[pad.padButton])
				{
					m_isPadTrigger[pad.padButton] = true;
				}
				else
				{
					m_isPadTrigger[pad.padButton] = false;
				}
				m_isPadPress[pad.padButton] = true;
			}
			else
			{
				m_isPadTrigger[pad.padButton] = false;
				m_isPadPress[pad.padButton] = false;
			}
		}
		float inputNormalize;
		inputNormalize = (float)triggerMax;
		//トリガーの押し込み量を0.0〜1.0に正規化
		m_leftTrigger = (float)m_state.Gamepad.bLeftTrigger / inputNormalize;
		m_rightTrigger = (float)m_state.Gamepad.bRightTrigger / inputNormalize;

		const int stickNum = 4;
		float padInput[stickNum] = 
		{
			m_state.Gamepad.sThumbLX,
			m_state.Gamepad.sThumbLY,
			m_state.Gamepad.sThumbRX,
			m_state.Gamepad.sThumbRY,
		};
		float* padOutput[stickNum] = 
		{
			&m_leftStickX,
			&m_leftStickY,
			&m_rightStickX,
			&m_rightStickY,
		};
		for (int i = 0; i < stickNum; i++)
		{
			if (0 < padInput)
			{
				inputNormalize = SHRT_MAX;
			}
			else
			{
				inputNormalize = -SHRT_MIN;
			}
			//スティックの入力量を-1.0〜1.0に正規化
			*padOutput[i] = padInput[i] / inputNormalize;
			//入力量が小さい場合誤差とみなして値を0にする
			if (*padOutput[i] < inputDeadZone && -inputDeadZone < *padOutput[i])
			{
				*padOutput[i] = 0.0f;
			}
		}

	}
	else
	{
		//接続されてない場合キーボードで入力。
		for (const CorrespondencePad& pad : correspondencePad)
		{
			if (GetAsyncKeyState(pad.keyCode))
			{
				if (!m_isPadPress[pad.padButton])
				{
					m_isPadTrigger[pad.padButton] = true;
				}
				else
				{
					m_isPadTrigger[pad.padButton] = false;
				}
				m_isPadPress[pad.padButton] = true;
			}
			else
			{
				m_isPadPress[pad.padButton] = false;
			}
		}
		m_leftStickX = 0.0f;
		m_leftStickY = 0.0f;
		m_rightStickX = 0.0f;
		m_rightStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)) {
			m_rightStickX = -1.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			m_rightStickX = 1.0f;
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_rightStickY = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_rightStickY = -1.0f;
		}

		if (GetAsyncKeyState('A')) {
			m_leftStickX = -1.0f;
		}
		else if (GetAsyncKeyState('D')) {
			m_leftStickX = 1.0f;
		}
		if (GetAsyncKeyState('W')) {
			m_leftStickY = 1.0f;
		}
		else if (GetAsyncKeyState('S')) {
			m_leftStickY = -1.0f;
		}
	}
}