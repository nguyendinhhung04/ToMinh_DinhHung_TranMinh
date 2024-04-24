#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
#include "Bullet.h"
#include "enemy.h"

class TextureManager;
class BaseWeapon : public BaseObject {
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

	float m_range;
	float m_fireSpeed;
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;

	//

	// damage
	float damage;
	float m_timeSinceLastFire;
	std::shared_ptr<Bullet> BulletOfWeapon;

	std::string bullet_path;
public:
	BaseWeapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	BaseWeapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime,std::string bullet_path,float damage);
	~BaseWeapon();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;

	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	double		GetRotation();
	SDL_RendererFlip GetFlip();
	void SetFlip(SDL_RendererFlip flip);

	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	//Moving
	float m_MoveSpeed;

	//Rotation
	void Flip(bool targetDir);
	//void AimToEnemy(Vector2 enemy);
	void AimToEnemy(std::shared_ptr<enemy> enemy);

	virtual std::shared_ptr<Bullet> Fire( float deltaTime, std::vector<std::shared_ptr<enemy>> tempVector);
	bool CheckEnemyInRange(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos);

	float getDamage() { return damage; }
	void setDamage(float damage) {if(BulletOfWeapon != NULL) this->BulletOfWeapon->setDamage(damage);}
};
