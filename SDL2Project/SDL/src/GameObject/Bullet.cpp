#include "Bullet.h"
#include "TextureManager.h"
#include <cmath>
#define INITIAL_HP 100
#define INITIAL_SPEED 700
//#define INITIAL_DAMAGE 10
#define INITIAL_DAMAGE 10000


Bullet::Bullet(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{

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
	m_hp = INITIAL_HP;
	m_timeSinceLastDeduction = 0;
	m_speed = INITIAL_SPEED;
	m_damage = INITIAL_DAMAGE;
}
Bullet::~Bullet()
{

}

void Bullet::Init()
{

}

void Bullet::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void Bullet::Update(float deltatime)
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

void Bullet::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void Bullet::SetRotation(double angle)
{
	m_angle = angle;
}

void Bullet::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 Bullet::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void Bullet::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Bullet::GetWidth()
{
	return m_iWidth;
}

int Bullet::GetHeight()
{
	return m_iHeight;
}


void Bullet::Flip(bool targetDir)
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


void Bullet::MoveLeft(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
}

void Bullet::MoveRight(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
}
void Bullet::MoveUp(float deltaTime, float speed)
{
	m_position.y -= speed * deltaTime;
}
void Bullet::MoveDown(float deltaTime, float speed)
{
	m_position.y += speed * deltaTime;
}

void Bullet::MoveLeftDown(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
	m_position.y += speed * deltaTime;
}

void Bullet::MoveLeftUp(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
	m_position.y -= speed * deltaTime;
}

void Bullet::MoveRightUp(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
	m_position.y -= speed * deltaTime;
}


void Bullet::MoveRightDown(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
	m_position.y += speed * deltaTime;
}


bool Bullet::CheckCollision(Vector2 other, int width, int height)
{
	if (Get2DPosition().x > 2000 || Get2DPosition().y > 1500) 
	{
		return true;
	}

	bool check;
	int e_x_left = other.x;
	int e_x_right = e_x_left + width;
	int e_y_top = other.y;
	int e_y_bot = e_y_top + height;
	int x_left = m_position.x;
	int x_right = x_left + m_iWidth;
	int y_top = m_position.y;
	int y_bot = y_top + m_iHeight;
	if (x_left <= e_x_left && e_x_left <= x_right && y_top <= e_y_bot && e_y_bot <= y_bot) return true;
	else if (x_left <= e_x_left && e_x_left <= x_right && e_y_top <= y_bot && y_bot <= e_y_bot) return true;
	else if (x_left >= e_x_left && x_left <= e_x_right && y_top <= e_y_bot && e_y_bot <= y_bot) return true;
	else if (x_left >= e_x_left && x_left <= e_x_right && e_y_top <= y_bot && y_bot <= e_y_bot) return true;
	return false;
}


void Bullet::SetTarget(Vector2 target)
{
	float x_dis = target.x - m_position.x;
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
	y_dis = target.y - m_position.y;

	float tan_value = x_dis / y_dis;
	cos_value = sqrt(1 / (1 + pow(tan_value, 2)));
	sin_value = cos_value * tan_value;
}



void Bullet::MoveToTarget( float deltaTime)
{
	if (y_dis < 0) {
		m_position.x -= sin_value * m_speed * deltaTime;
		m_position.y -= cos_value * m_speed * deltaTime;
	}
	else {
		m_position.x += sin_value * m_speed * deltaTime;
		m_position.y += cos_value * m_speed * deltaTime;
	}
}


float Bullet::GetDamageAmount()
{
	return m_damage;
}


