#include "stdafx.h"
#include "Player.h"
#include "../GameCamera/GameCamera.h"
#include "../Scene/GameScene.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	float ambient = 0.6f;
	float diffuseColor = 0.3f;
	m_light.SetAmbiemtLight({ ambient, ambient, ambient, 1.0f });
	m_light.SetDiffuseLightColor(0, { diffuseColor, diffuseColor, diffuseColor, 1.0f });
	m_light.SetDiffuseLightDirection(0, { 0.707f, 0.0f, 0.707f, 1.0f });

	m_rotation = rotation;
	m_position = position;
	m_scale = { 1.0f, 1.0f, 1.0f };
	m_characterController.Init(1.0f, 1.0f, m_position);
	m_characterController.SetMoveSpeed({ 0.0f, 0.0f, 0.0f });
	m_characterController.SetGravity(-20.0f);
	m_skinModel.SetShadowCasterFlg(true);
	m_skinModel.SetShadowReceiverFlg(true);
}

void Player::Start()
{
	m_skinModelData.LoadModelData("Assets/modelData/Unitychan.X", &m_anim);
	m_skinModel.Init(&m_skinModelData);
	m_skinModel.SetLight(&m_light);
	m_modelNormalMap.Load("Assets/modelData/utc_normal.tga");
	m_modelSpecularMap.Load("Assets/modelData/utc_spec.tga");
	m_skinModel.SetNormalMap(&m_modelNormalMap);
	m_skinModel.SetSpecularMap(&m_modelSpecularMap, &g_gameScene->GetCamera());
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_anim.SetAnimationEndTime(0, 0.8f);
}

void Player::Update()
{
	if (g_gameScene == nullptr)
	{
		return;
	}

	Move();
	Rotation();
	
	if (GetPad().IsPressButton(padButtonB))
	{
		m_anim.PlayAnimation(0);
	}

	if (m_position.y < -10.0f)
	{
		g_gameScene->GameOver();
	}
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_anim.Update(1.0f / 60.0f);
}

void Player::Move()
{
	//移動
	D3DXVECTOR3 moveSpeed = {0.0f, 0.0f, 0.0f};
	moveSpeed.y = m_characterController.GetMoveSpeed().y;
	Camera& camera = g_gameScene->GetCamera();
	//カメラの向きを移動方向として移動
	D3DXVECTOR3 front = camera.GetTarget() - camera.GetPosition();
	front.y = 0.0f;
	D3DXVec3Normalize(&front, &front);
	D3DXVECTOR3 side;
	//横への移動方向は外積を取って求める
	D3DXVec3Cross(&side, &front, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&side, &side);
	float speed = 30.0f;
	moveSpeed += -side * GetPad().GetLeftStickX() * speed;
	moveSpeed += front * GetPad().GetLeftStickY() * speed;
	if (GetPad().IsTriggerButton(padButtonA))
	{
		moveSpeed.y += 15.0f;
	}

	m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.Execute();
	m_position = m_characterController.GetPosition();
}

void Player::Rotation()
{
	D3DXVECTOR3 moveDir = m_characterController.GetMoveSpeed();
	moveDir.y = 0.0f;
	//モデルを回転
	if (0.0f < D3DXVec3Length(&moveDir))
	{
		D3DXMATRIX worldMat = m_skinModel.GetWorldMatrix();
		D3DXVECTOR3 front;
		front.x = 0.0f;
		front.y = 0.0f;
		front.z = 1.0f;
		D3DXVec3Normalize(&moveDir, &moveDir);
		D3DXVec3Normalize(&front, &front);
		float rad = acos(D3DXVec3Dot(&front, &moveDir));
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &front, &moveDir);
		if (cross.y < 0.0f)
		{
			rad = -rad;
		}
		D3DXQUATERNION multi;
		D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rad);
	}
}

void Player::Draw()
{
	m_skinModel.Draw(&g_gameScene->GetCamera().GetViewMatrix(), &g_gameScene->GetCamera().GetProjectionMatrix());
}
