#include "enemyBoomer.h"

enemyBoomer::enemyBoomer(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime, float HP, float power, float speed, float boomValue) : enemy(texture, spriteRow,frameCount, numAction, frameTime, HP,power,speed)
{
	this->boomValue = boomValue;
}

void enemyBoomer::specialSkill() 
{
	if (m_hp == 0)
	{
        float explosionRadius = 50.0f; // Define the radius of the explosion
        float explosionDamage = 50.0f; // Define the damage dealt by the explosion
		//code here
	}
}