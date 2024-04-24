#include "enemy.h"
#include "TextureManager.h"
#include <cmath>
#include <iostream>
#include <random>
#include <cstdlib> 
#define ENEMY_POWER 10
#define ENEMY_HP 100
enemy::enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime,float HP,float power,float speed) : BaseObject(texture)
{
	m_rotationDirection = true;
	
	m_pTexture = texture;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
	m_hp = HP;
	m_power = power;
	m_actualSize = 30;
	m_MoveSpeed = speed;
}
enemy::~enemy()
{

}

void enemy::Init()
{

}

void enemy::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void enemy::Update(float deltatime)
{
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

float enemy::getSpeed() { return m_MoveSpeed;}
void enemy::setSpeed(float s) { this->m_MoveSpeed = s; }

void enemy::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void enemy::SetRotation(double angle)
{
	m_angle = angle;
}

void enemy::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 enemy::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void enemy::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int enemy::GetWidth()
{
	return m_iWidth;
}

int enemy::GetHeight()
{
	return m_iHeight;
}



void enemy::MoveLeft(float deltaTime, float speed)
{
	printf("LeftFunc");
	m_position.x -= speed * deltaTime;
}

void enemy::MoveRight(float deltaTime, float speed)
{
	printf("RightFunc");
	m_position.x += speed * deltaTime;
}
void enemy::MoveUp(float deltaTime, float speed)
{
	printf("UpFunc");
	m_position.y -= speed * deltaTime;
}
void enemy::MoveDown(float deltaTime, float speed)
{
	printf("DownFunc");
	m_position.y += speed * deltaTime;
}

void enemy::MoveLeftDown(float deltaTime, float speed)
{
	printf("LeftDownFunc");
	m_position.x -= speed * deltaTime;
	m_position.y += speed * deltaTime;
}

void enemy::MoveLeftUp(float deltaTime, float speed)
{
	printf("LeftUpFunc");
	m_position.x -= speed * deltaTime;
	m_position.y -= speed * deltaTime;
}

void enemy::MoveRightUp(float deltaTime, float speed)
{
	printf("RightUpFunc");
	m_position.x += speed * deltaTime;
	m_position.y -= speed * deltaTime;
}


void enemy::MoveRightDown(float deltaTime, float speed)
{
	printf("RightUpFunc");
	m_position.x += speed * deltaTime;
	m_position.y += speed * deltaTime;
}



void enemy::Flip(bool targetDir)
{
	if (targetDir != m_rotationDirection)
	{
		m_rotationDirection = !m_rotationDirection;
		if (m_rotationDirection == true) {
			SetFlip(SDL_FLIP_NONE);
		}
		else {
			SetFlip(SDL_FLIP_HORIZONTAL);
		}
	}
}


bool enemy::CheckCollisionX(std::shared_ptr<enemy> other)
{
	if (m_position.x == other->Get2DPosition().x && m_position.y == other->Get2DPosition().y)
	{
		return false;
	}
	bool check = false;
	if ((other->Get2DPosition().x > m_position.x - m_actualSize && other->Get2DPosition().x < m_position.x + m_iWidth - m_actualSize) || (m_position.x > other->Get2DPosition().x - m_actualSize && m_position.x < other->Get2DPosition().x + other->GetWidth() - m_actualSize))
	{
		if ((other->Get2DPosition().y > m_position.y - m_actualSize && other->Get2DPosition().y < m_position.y + m_iHeight - m_actualSize) || (m_position.y > other->Get2DPosition().y - m_actualSize && m_position.y < other->Get2DPosition().y + other->GetHeight() - m_actualSize))
		{
			if ((other->Get2DPosition().x > m_position.x - m_actualSize && other->Get2DPosition().x < m_position.x + m_iWidth - m_actualSize) || (m_position.x > other->Get2DPosition().x - m_actualSize && m_position.x < other->Get2DPosition().x + other->GetWidth() - m_actualSize))
			{
				check = true;
			}
		}
	}
	return check;
}

bool enemy::CheckCollisionY(std::shared_ptr<enemy> other)
{
	if (m_position.x == other->Get2DPosition().x && m_position.y == other->Get2DPosition().y)
	{
		return false;
	}
	bool check = false;
	if ((other->Get2DPosition().x > m_position.x - m_actualSize && other->Get2DPosition().x < m_position.x + m_iWidth - m_actualSize) || (m_position.x > other->Get2DPosition().x - m_actualSize && m_position.x < other->Get2DPosition().x + other->GetWidth() - m_actualSize))
	{
		if ((other->Get2DPosition().y > m_position.y - m_actualSize && other->Get2DPosition().y < m_position.y + m_iHeight - m_actualSize) || (m_position.y > other->Get2DPosition().y - m_actualSize && m_position.y < other->Get2DPosition().y + other->GetHeight() - m_actualSize))
		{
			if ((other->Get2DPosition().y > m_position.y - m_actualSize && other->Get2DPosition().y < m_position.y + m_iHeight - m_actualSize) || (m_position.y > other->Get2DPosition().y - m_actualSize && m_position.y < other->Get2DPosition().y + other->GetHeight() - m_actualSize))
			{
				check = true;
			}
		}
	}
	return check;
}

void enemy::MoveToCharacterX(float deltaTime, float speed, Vector2 other, std::vector<std::shared_ptr<enemy>> m_vectorEnemy)
{


	float x_dis = other.x - m_position.x;
	if (x_dis > 0)
	{
		bool temp = true;
		Flip(temp);
	}
	else
	{
		bool temp = false;
		Flip(temp);
	}
	float y_dis = other.y - m_position.y;
	if ((!(abs(x_dis) < 30)))
	{

		float tan_value = x_dis / y_dis;
		float cos_value = sqrt(1 / (1 + pow(tan_value, 2)));
		float sin_value = cos_value * tan_value;


		if (y_dis < 0) {
			m_position.x -= sin_value * speed * deltaTime;
			for (auto it = m_vectorEnemy.begin(); it != m_vectorEnemy.end(); ++it)
			{
				if (CheckCollisionX(*it))
				{
					m_position.x += sin_value * speed * deltaTime;
					break;
				}
			}
		}
		else {
			m_position.x += sin_value * speed * deltaTime;
			for (auto it = m_vectorEnemy.begin(); it != m_vectorEnemy.end(); ++it)
			{
				if (CheckCollisionX(*it))
				{
					m_position.x -= sin_value * speed * deltaTime;
					break;
				}
			}
		}
	}
}

void enemy::MoveToCharacterY(float deltaTime, float speed, Vector2 other, std::vector<std::shared_ptr<enemy>> m_vectorEnemy)
{


	float x_dis = other.x - m_position.x;
	float y_dis = other.y - m_position.y;
	if ((!(abs(y_dis) < 30)))
	{

		float tan_value = x_dis / y_dis;
		float cos_value = sqrt(1 / (1 + pow(tan_value, 2)));
		float sin_value = cos_value * tan_value;


		if (y_dis < 0) {
			m_position.y -= cos_value * speed * deltaTime;
			for (auto it = m_vectorEnemy.begin(); it != m_vectorEnemy.end(); ++it)
			{
				if (CheckCollisionY(*it))
				{
					m_position.y += cos_value * speed * deltaTime;
					break;
				}
			}
		}
		else {
			m_position.y += cos_value * speed * deltaTime;
			for (auto it = m_vectorEnemy.begin(); it != m_vectorEnemy.end(); ++it)
			{
				if (CheckCollisionY(*it))
				{
					m_position.y -= cos_value * speed * deltaTime;
					break;
				}
			}
		}
	}
}

int enemy::getPower()
{
	return m_power;
}


void enemy::Damaged(float bullet_damgage)
{
	m_hp -= bullet_damgage;
}

float enemy::GetHP()
{
	return m_hp;
}

void enemy::specialSkill()
{
	// this is special skill of enemy
}