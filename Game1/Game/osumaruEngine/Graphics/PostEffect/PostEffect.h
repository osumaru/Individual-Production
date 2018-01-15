#pragma once
#include "MonochromeFilter.h"
#include "Bloom.h"
#include "DepthOfField.h"
//ポストエフェクト

class PostEffect
{
public:
	PostEffect();

	~PostEffect();

	void Init();

	void Draw();

	DepthOfField& GetDepthOfField()
	{
		return m_dof;
	}
private:
	Bloom				m_bloom;		//ブルーム
	MonochromeFilter	m_monochrome;	//モノクロフィルター
	DepthOfField		m_dof;			//被写界深度
	Primitive			m_primitive;	//プリミティブ
	LPD3DXEFFECT		m_pEffect;		//エフェクト
	LPDIRECT3DSURFACE9	m_frameBuffer;	//バックバッファ
	LPDIRECT3DSURFACE9	m_depthBuffer;	//デプスステンシルバッファ
};