#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
#include <SDL_mixer.h>
class TextureManager;
class Bullet : public BaseObject {
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
	int			m_animSpeed;
	bool		m_rotationDirection;
	int m_numAction; //start from 1,2,3...

	float m_speed;
	float m_damage;
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;

	// HP
	int m_hp;
	float m_timeSinceLastDeduction;
	float cos_value;
	float sin_value;
	float y_dis;

	//sound
	char* soundPath;
	float isExistSound;
	Mix_Chunk* gScratch = NULL;
public:
	Bullet(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	Bullet(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime, char* soundPath);
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
	void SetTarget(Vector2 target);
	bool CheckCollision(Vector2 other, int width, int height);
	void MoveToTarget(float deltaTime);

	float GetDamageAmount();


	//float getDamage() { return m_damage; }
	void setDamage(float x) { m_damage = x; }
};
