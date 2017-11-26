#pragma once
#include "MapChip.h"
//�ړ����x�ɉ����x������MoveFloor

class HindranceObject : public MapChip
{
public:
	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation, char* modelName, Animation* anim = nullptr)override;

	//�X�V�֐�
	void Update()override;
private:
	float			m_timer;			//��莞�Ԃ��ƈړ����x�𔽓]�����邽�߂̃^�C�}�[
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x
	D3DXVECTOR3		m_acceleration;		//�����x
	RigidBody		m_rigidBody;		//����
	BoxCollider		m_boxCollider;		//�R���C�_�[
	bool			m_isChild;			//�q�������邩�ǂ���
	float			m_timerLimit;		//�^�C�}�[�̌��E
};