#pragma once
#include "Text.h"

class TextTimer : public Text
{
public:
	TextTimer(std::string fontPath, SDL_Color textColor);

	void Update(float deltatime) override;

	void SetTime(float time);
	float GetTime();
	void Pause();
	void Resume();

protected:
	float m_time;
	bool isCounting;



};