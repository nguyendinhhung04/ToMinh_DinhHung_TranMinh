#pragma once
#include "BaseObject.h"
#include "enemy.h"
#include "Bullet.h"
#include "SpriteAnimation.h"
class Weapon : public BaseObject
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
	bool		m_rotationDirection;
	int m_numAction; //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;
	//std::vector<Bullet*> m_bulletOfWeapon;
	//Bullet* m_bulletOfWeapon;
	std::vector<std::shared_ptr<Bullet>> m_bullets;
	int m_fireSpeed;
	float m_range;
	Vector2 m_initPosition;
	float currentTime;
public :
	Weapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~Weapon();

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
	void Flip(bool targetDir);

	//follow player
	void followPlayer(std::shared_ptr<SpriteAnimation> player);

	//Fire
	void Fire(Vector2 other);
	void FireP2(SDL_Renderer* renderer);
	//range
	bool IsEnemyInRange(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos);
	void initBullet(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos, float deltaTime);
	void UpdateBullets(float deltaTime);
};

