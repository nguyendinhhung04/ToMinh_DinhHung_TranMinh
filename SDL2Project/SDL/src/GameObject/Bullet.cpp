#include "Bullet.h"
#include "TextureManager.h"
#include <cmath>
#define SPEED 10
#define DAMAGE 20
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
	m_speed = SPEED;
	m_damage = DAMAGE;
	Init();
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



void Bullet::MoveLeft(float deltaTime, float speed)
{
	bool temp = false;
	m_position.x -= speed * deltaTime;
}

void Bullet::MoveRight(float deltaTime, float speed)
{
	bool temp = true;
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
	m_position.x -= speed * deltaTime;
	m_position.y += speed * deltaTime;
}

void Bullet::MoveLeftUp(float deltaTime, float speed)
{
	bool temp = false;
	m_position.x -= speed * deltaTime;
	m_position.y -= speed * deltaTime;
}

void Bullet::MoveRightUp(float deltaTime, float speed)
{
	bool temp = true;
	m_position.x += speed * deltaTime;
	m_position.y -= speed * deltaTime;
}


void Bullet::MoveRightDown(float deltaTime, float speed)
{
	bool temp = true;
	m_position.x += speed * deltaTime;
	m_position.y += speed * deltaTime;
}



void Bullet::MoveToTarget( Vector2 other)
{
	float x_dis = other.x - m_position.x;
	float y_dis = other.y - m_position.y;
	if ((!(abs(x_dis) < 10 && abs(y_dis) < 10)))
	{

		float tan_value = x_dis / y_dis;
		float cos_value = sqrt(1 / (1 + pow(tan_value, 2)));
		float sin_value = cos_value * tan_value;
		//printf("%f %f____%f %f %f\n",x_dis,y_dis, sin_value, cos_value, tan_value);


		if (y_dis < 0) {
			m_position.x -= sin_value * m_speed;
			m_position.y -= cos_value * m_speed;
		}
		else {
			m_position.x += sin_value * m_speed;
			m_position.y += cos_value * m_speed;
		}

		//m_position.y += cos_value * speed;

	}
}
