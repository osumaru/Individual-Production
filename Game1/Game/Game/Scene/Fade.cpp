#include "stdafx.h"
#include "Fade.h"

Fade* g_pFade = nullptr;

Fade::Fade()
{
	m_alpha = 0.0f;
	m_fadeTime = 0.5f;
	m_timer = m_fadeTime;
	m_state = enFadeOut;
}

Fade::~Fade()
{

}

void Fade::Init()
{
	m_sprite.Init("Assets/sprite/Fade.png");
	m_sprite.SetSize(D3DXVECTOR2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT));
}

void Fade::FadeIn()
{
	m_timer = 0.0f;
	m_state = enFadeIn;
	m_isExcute = true;
}
void Fade::FadeOut()
{
	m_timer = 0.0f;
	m_state = enFadeOut;
	m_isExcute = true;
}

void Fade::Update()
{
	if (m_timer < m_fadeTime)
	{
		m_timer += 1.0f / 60.0f;
	}
	else
	{
		m_isExcute = false;
		m_timer = m_fadeTime;
	}
	float alpha = m_timer / m_fadeTime;
	if (m_state == enFadeIn)
	{
		alpha = 1.0f - alpha;
	}

	m_sprite.SetAlpha(alpha);
}

void Fade::AfterDraw()
{
	m_sprite.Draw();
}