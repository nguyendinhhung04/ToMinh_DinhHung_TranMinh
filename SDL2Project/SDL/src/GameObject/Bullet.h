#pragma once
#include "BaseObject.h"
class Bullet : public BaseObject
{
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float			m_numFrames;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 1,2,3
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	Uint32 m_lastUpdate;
	int m_numAction; //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;
	int m_speed;
	int m_damage;
public:
	Bullet(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Bullet();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;

	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int GetWidth();
	int GetHeight();

	void MoveLeft(float deltaTime, float speed);
	void MoveRight(float deltaTime, float speed);
	void MoveUp(float deltaTime, float speed);
	void MoveDown(float deltaTime, float speed);
	void MoveLeftDown(float deltaTime, float speed);
	void MoveLeftUp(float deltaTime, float speed);
	void MoveRightUp(float deltaTime, float speed);
	void MoveRightDown(float deltaTime, float speed);

	//
	void MoveToTarget(Vector2 other);

	//Bullet movement
	void BulletMovement();
};

