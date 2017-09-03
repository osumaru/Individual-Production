#pragma once
#include "Primitive.h"
class Texture;

//スプライトのクラス
class Sprite
{
public:

	Sprite();

	~Sprite();
	//初期化
	void Init(char *filePath);

	//描画
	void Draw();

	//座標をセット
	void SetPosition(D3DXVECTOR2 position)
	{
		m_position = position;
	}

	//座標を取得
	D3DXVECTOR2 GetPosition()
	{
		return m_position;
	}

	//サイズを設定
	void SetSize(D3DXVECTOR2 size)
	{
		m_size = size;
	}

	//サイズを取得
	D3DXVECTOR2 GetSize()
	{
		return m_size;
	}
	//メモリを解放
	void Release();

private:
	Texture*		m_pTexture;			//テクスチャ
	D3DXVECTOR2		m_position;			//スプライトのウィンドウ上での座標
	D3DXVECTOR2		m_centerPosition;	//スプライトの基点を表す座標
	D3DXVECTOR2		m_size;
	LPD3DXEFFECT	m_pEffect;
	Primitive		m_primitive;
	LPD3DXSPRITE	m_spite;
};