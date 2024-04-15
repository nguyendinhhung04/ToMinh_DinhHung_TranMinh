#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "enemy.h"
#include "BaseWeapon.h"

class Sprite2D;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;

private:

	void DrawPauseScreen(SDL_Renderer* renderer);

	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;               
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	//std::list<std::shared_ptr<enemy>> m_listEnemy;
	std::vector<std::shared_ptr<enemy>> m_vectorEnemy;
	std::shared_ptr<enemy> monster;
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<BaseWeapon> weapon;
	std::vector<std::shared_ptr<BaseWeapon>> m_vectorWeapon;
	std::shared_ptr<Bullet> bullet;
	std::vector<std::shared_ptr<Bullet>> m_vectorBullet;




	SDL_Rect m_darkOverlay;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;

	bool m_isPlaying;

};

