#include "SpriteAnimation.h"
#include "TextureManager.h"
#include <cmath>
#define INITIAL_HP 100
SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_MoveSpeed = (float)(250);           //
	m_rotationDirection = true;           //True == Right,  false == left
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
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	gScratch = Mix_LoadWAV("Data/Sounds/Footstep SFX.wav");
}
SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Init()
{

}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void SpriteAnimation::Update(float deltatime)
{
	m_currentTicks += deltatime;
		if(m_currentTicks  >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{ 
	m_flip = flip;
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}


void SpriteAnimation::Flip(bool targetDir)
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


void SpriteAnimation::MoveLeft(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835 || m_position.y < 80 || m_position.y >942)
	{
		printf("OUT");
		m_position.x += speed * deltaTime;
	}
}

void SpriteAnimation::MoveRight(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835 || m_position.y < 80 || m_position.y >942)
	{
		m_position.x -= speed * deltaTime;
	}
}
void SpriteAnimation::MoveUp(float deltaTime, float speed)
{
	m_position.y -= speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835 || m_position.y < 80 || m_position.y >942)
	{
		m_position.y += speed * deltaTime;
	}
}
void SpriteAnimation::MoveDown(float deltaTime, float speed)
{
	m_position.y += speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835 || m_position.y < 80 || m_position.y >942)
	{
		m_position.y -= speed * deltaTime;
	}
}

void SpriteAnimation::MoveLeftDown(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
	m_position.y += speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835)
	{
		m_position.x += speed * deltaTime;
	}
	if (m_position.y < 80 || m_position.y >942)
	{
		m_position.y -= speed * deltaTime;
	}
}

void SpriteAnimation::MoveLeftUp(float deltaTime, float speed)
{
	bool temp = false;
	Flip(temp);
	m_position.x -= speed * deltaTime;
	m_position.y -= speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835)
	{
		m_position.x += speed * deltaTime;
	}
	if (m_position.y < 80 || m_position.y >942)
	{
		m_position.y += speed * deltaTime;
	}
}

void SpriteAnimation::MoveRightUp(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
	m_position.y -= speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835)
	{
		m_position.x -= speed * deltaTime;
	}
	if (m_position.y < 80 || m_position.y >942)
	{
		m_position.y += speed * deltaTime;
	}
}


void SpriteAnimation::MoveRightDown(float deltaTime, float speed)
{
	bool temp = true;
	Flip(temp);
	m_position.x += speed * deltaTime;
	m_position.y += speed * deltaTime;
	Mix_PlayChannel(-1, gScratch, 0);
	if (m_position.x < 111 || m_position.x >1835)
	{
		m_position.x -= speed * deltaTime;
	}
	if (m_position.y < 80 || m_position.y >942)
	{
		m_position.y -= speed * deltaTime;
	}

}


bool SpriteAnimation::CheckCollision(Vector2 other, int width, int height)
{
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


// minus = enemy_power
void SpriteAnimation::minusHP(int enemy_power, float deltaTime)
{
	m_timeSinceLastDeduction += deltaTime;
	if (m_timeSinceLastDeduction >= 1.0f)
	{
		m_hp -= enemy_power;
		m_timeSinceLastDeduction = 0;
	}
}

int SpriteAnimation::getHP()
{
	return m_hp;
}

