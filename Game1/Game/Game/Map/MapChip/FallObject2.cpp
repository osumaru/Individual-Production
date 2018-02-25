#include "stdafx.h"
#include "FallObject2.h"
#include "../../Scene/GameScene.h"

FallObject2::FallObject2() :
	m_isFall(false),
	m_rigidBody(),
	m_boxCollider(),
	m_particle(nullptr),
	m_timer(0.0f),
	m_animationTimer(0.0f),
	m_animationMove(0.0f, 0.0f, 0.0f),
	m_frameNum(0),
	m_pSound(nullptr),
	m_soundVolume(1.0f)
{
}

FallObject2::~FallObject2()
{
	ParticleDelete();
	SoundDelete();
}

void FallObject2::Init(const D3DXVECTOR3& position, const D3DXQUATERNION& rotation, const char* modelName, Animation* anim)
{
	MapChip::Init(position, rotation, modelName);
	//剛体を初期化
	MeshCollider mesh;
	mesh.CreateFromSkinModel(&m_skinModel, NULL);
	D3DXVECTOR3 aabb = (mesh.GetAabbMax() - mesh.GetAabbMin()) / 2.0f;
	m_boxCollider.Create(btVector3(aabb.x, aabb.y, aabb.z));
	RigidBodyInfo rbInfo;
	rbInfo.mass = 0.0f;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_boxCollider;
	m_rigidBody.Create(rbInfo);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);
	//パーティクルを初期化
	//m_particle = New<ParticleEmitter>(CAMERA_PRIORITY);
	//m_particle->Init({
	//	"Assets/particle/WallDust.png",						//テクスチャのファイルパス
	//	0.4f,												//パーティクルの横幅
	//	0.4f,												//パーティクルの縦幅
	//	{ 0.0f, 0.0f, 1.0f, 1.0f },							//テクスチャのuv。xyが左上のuvでzwが右下のuv
	//	{ aabb.x, 3.0f, aabb.z },					//パーティクルの座標のランダム幅
	//	{ 0.0f, -0.5f, 0.0f },								//パーティクルの重力
	//	1.3f,												//パーティクルの寿命
	//	1.0f,												//パーティクルが出るまでのインターバル
	//	0.0f,												//エミッターの寿命
	//	{ m_position.x, m_position.y - 11.0f, m_position.z },//エミッターの座標
	//	2,													//1フレームで出るパーティクルの数
	//	true												//最初にパーティクルをエミットする時だけ時間をランダムにするか
	//}
	//, &GetGameScene().GetCamera());
	m_skinModel.SetShaderTechnique(enShaderTechniqueDithering);
	m_animationMove.x = (float)GetRandom().GetRandDouble();
	m_animationMove.y = (float)GetRandom().GetRandDouble();
	m_animationMove.z = (float)GetRandom().GetRandDouble();
	D3DXVec3Normalize(&m_animationMove, &m_animationMove);
	m_animationMove *= 0.18f;
}



void FallObject2::Update()
{
	MapChip::Update();
	if (!m_isActive)
	{
		return;
	}
	//プレイヤーが上に乗ったら落ち始める
	if (m_rigidBody.GetBody()->getPlayerCollisionGroundFlg() && !m_isFall)
	{
		m_isFall = true;
		ParticleDelete();
		m_pSound = New<SoundSource>(0);
		m_pSound->Init("Assets/sound/seismic.wav");
		m_pSound->SetVolume(m_soundVolume);
		m_pSound->Play(true);
	}
	if (m_isFall)
	{
		const float animationLimit = 1.2f;
		if (m_animationTimer < animationLimit)
		{

			m_position += m_animationMove;
			if (m_frameNum % 2 == 0)
			{
				m_animationMove *= -1.0f;
			}
			m_animationTimer += GetGameTime().GetDeltaFrameTime();
			m_frameNum++;
		}
		else
		{
			m_position.y -= 0.2f;
			m_timer += GetGameTime().GetDeltaFrameTime();
			//落ち始めてある程度時間がたつと消える
			if (3.5f < m_timer)
			{
				MapChipDelete();
			}
			if (0.0f < m_soundVolume)
			{
				m_pSound->SetVolume(m_soundVolume);
				m_soundVolume -= GetGameTime().GetDeltaFrameTime() * 0.5f;
			}
			else
			{
				SoundDelete();
			}
		}
	}
	//剛体を移動
	m_rigidBody.SetPosition(m_position);
	m_rigidBody.SetPlayerCollisionGroundFlg(false);

	m_skinModel.Update(m_position, m_rotation, m_scale);
}

void FallObject2::ParticleDelete()
{
	if (m_particle != nullptr)
	{
		Delete(m_particle);
		m_particle = nullptr;
	}
}

void FallObject2::SoundDelete()
{
	if (m_pSound != nullptr)
	{
		Delete(m_pSound);
		m_pSound = nullptr;
	}
}


void FallObject2::Draw()
{
	MapChip::Draw();
	GetPhysicsWorld().DebugDraw(m_rigidBody.GetBody()->getWorldTransform(), m_rigidBody.GetBody()->getCollisionShape());
}