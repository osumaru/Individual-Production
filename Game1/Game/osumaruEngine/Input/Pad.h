#pragma once
//�p�b�h�̓��͂��擾����N���X

enum PadButton
{
	padButtonUp,
	padButtonDown,
	padButtonLeft,
	padButtonRight,
	padButtonA,
	padButtonB,
	padButtonX,
	padButtonY,
	padButtonSelect,
	padButtonStart,
	padButtonRB,
	padButtonRStickPush,
	padButtonLB,
	padButtonLStickPush,
	padButtonNum,

};

class Pad
{
public:

	//�R���X�g���N�^
	Pad();

	//�f�X�g���N�^
	~Pad();

	//�X�V
	void Update();

	/*
	�{�^���������Ă��邩���ׂ�֐�
	button			������Ă��邩���ׂ����{�^����enum
	*/
	bool IsPressButton(PadButton button)
	{
		return m_isPadPress[button];
	}

	//���X�e�B�b�N��X���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetLeftStickX()
	{
		return m_leftStickX;
	}

	//���X�e�B�b�N��Y���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetLeftStickY()
	{
		return m_leftStickY;
	}

	//�E�X�e�B�b�N��X���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetRightStickX()
	{
		return m_rightStickX;
	}

	//�E�X�e�B�b�N��Y���̓��͗ʂ��擾(-1.0����1.0�̊�
	float GetRightStickY()
	{
		return m_rightStickY;
	}

	//�p�b�h�̍��̃g���K�[�̓��͗ʂ��擾(0.0����1.0
	float GetLeftTrigger()
	{
		return m_leftTrigger;
	}
	//�p�b�h�̉E�̃g���K�[�̓��͗ʂ��擾(0.0����1.0
	float GetRightTrigger()
	{
		return m_rightTrigger;
	}

private:
	int				m_padNum;					//�p�b�h�̔ԍ�
	float			m_rightStickX;				//�E�X�e�B�b�N��X���̓��͗�
	float			m_rightStickY;				//�E�X�e�B�b�N��Y���̓��͗�
	float			m_leftStickX;				//���X�e�B�b�N��X���̓��͗�
	float			m_leftStickY;				//���X�e�B�b�N��Y���̓��͗�
	float			m_rightTrigger;				//�E�g���K�[�̓��͗�
	float			m_leftTrigger;				//���g���K�[�̓��͗�
	bool			m_isPadPress[padButtonNum];	//�e�{�^����������Ă��邩�H
	XINPUT_STATE	m_state;						//�p�b�h�̓��͏��
};