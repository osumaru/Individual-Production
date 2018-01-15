#pragma once
//ゲームカメラクラス

class GameCamera : public GameObject
{
public:
	//コンストラクタ
	GameCamera();
	
	//デストラクタ
	~GameCamera();

	//初期化関数
	void Init();

	//更新関数
	void Update()override;

	//カメラの取得
	Camera& GetCamera()
	{
		return m_camera;
	}

private:
	D3DXQUATERNION	m_rotation;		//カメラの回転
	Camera			m_camera;		//カメラ
	float			m_angleX;		//カメラがX方向を軸に回転している角度	
};