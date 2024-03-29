#pragma once
//タイム表示のＨＵＤ

class TimeSprite : public GameObject
{
public:

	//コンストラクタ
	TimeSprite();

	//デストラクタ
	~TimeSprite()override;

	//初期化関数
	bool Start()override;

	//更新関数
	void Update()override;

	//描画関数
	void AfterDraw()override;

	//タイム取得
	float GetTime() const
	{
		return m_time;
	}

	//アクティブかのフラグを設定
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	static const int	NUM_MAX = 10;						//一桁の数字の数
	static const int	DIGIT_MAX = 2;						//桁の数
	static const int	TIME_MAX = 3;						//区切りの数
	Sprite				m_timeSprite;						//タイムスプライト
	Sprite				m_colonSprite[TIME_MAX - 1];		//区切りのスプライト
	Sprite				m_numSprite[TIME_MAX][DIGIT_MAX];	//数字のスプライト
	Texture*			m_numTexture[NUM_MAX];				//数字のテクスチャ
	float				m_time;								//タイム
	bool				m_isActive;							//アクティブか？
};