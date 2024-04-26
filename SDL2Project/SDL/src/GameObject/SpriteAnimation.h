#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
#include <SDL_mixer.h>
class TextureManager;
class SpriteAnimation : public BaseObject{
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float			m_numFrames;
	int			m_currentFrame;
	
	float		m_currentTime;
	//int			m_spriteRow; //start 1,2,3
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	int m_numAction;
	Uint32 m_lastUpdate;
	int			m_animSpeed;
	bool		m_rotationDirection;
	 //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;

	// HP
	float m_hp;
	float m_timeSinceLastDeduction;
	float m_timeSinceLastAnim;

	//foot step sound
	float m_timeSinceLastSound;
	Mix_Chunk* gScratch = NULL;


public:
	int			m_spriteRow;
	float		m_frameTime;

	SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;

	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	void SetFlip (SDL_RendererFlip flip);

	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
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

	//Rotation
	void Flip(bool targetDir);

	//HP
	bool CheckCollision(Vector2 other, int width, int height);
	void minusHP(int, float);
	float getHP();
	float GetSpeed() { return m_MoveSpeed; }


	void setHP(float hp) { this->m_hp = hp; }

	void GotHit(float deltaTime);
	bool isGotHit;

	//sound
	//bool loadMedia();
	//void close();
};
