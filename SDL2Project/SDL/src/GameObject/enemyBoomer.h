#pragma once
#include "enemy.h"
class enemyBoomer : public enemy
{
private :
	float boomValue;
public :
	enemyBoomer(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime, float HP, float power, float speed,float boomValue);
	void specialSkill() override;
};

