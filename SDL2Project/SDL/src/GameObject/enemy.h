#pragma once
#include "BaseObject.h"

class enemy :public BaseObject
{
protected:
	Vector2		m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float		m_numFrames;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 1,2,3
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	Uint32 m_lastUpdate;
	int			m_animSpeed;
	int m_numAction; //start from 1,2,3...
	bool		m_rotationDirection;
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;
	//enemy power
	int m_power;
public:
	enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~enemy();

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

	//Moving for enemy
	void MoveToCharacter(float deltaTime, float speed, Vector2 other);

	//Moving
	float m_MoveSpeed;
	void MoveLeft(float deltaTime, float speed);
	void MoveRight(float deltaTime, float speed);
	void MoveUp(float deltaTime, float speed);
	void MoveDown(float deltaTime, float speed);
	void MoveLeftDown(float deltaTime, float speed);
	void MoveLeftUp(float deltaTime, float speed);
	void MoveRightUp(float deltaTime, float speed);
	void MoveRightDown(float deltaTime, float speed);

	//Rotation for Enemy
	void Flip(bool targetDir);
	int getPower();
};

