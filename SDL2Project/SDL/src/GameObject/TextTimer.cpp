#include "TextTimer.h"

TextTimer::TextTimer(std::string fontPath, SDL_Color textColor): Text(fontPath, textColor)
{
	this->isCounting = false;
}

void TextTimer::SetTime(float time)
{
	m_time = time;
	isCounting = true;
	m_pTexture->LoadFromRendererText(m_Font, std::to_string(int(m_time)) + "s", m_TextColor);
}

float TextTimer::GetTime()
{
	return m_time;
}

void TextTimer::Update(float deltatime)
{
	if (isCounting == true)
	{
		m_time -= deltatime;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->LoadFromRendererText(m_Font, std::to_string(int(m_time)) + "s", m_TextColor);
	}
}

void TextTimer::Pause()
{
	isCounting = false;
}


void TextTimer::Resume()
{
	isCounting = true;
}

