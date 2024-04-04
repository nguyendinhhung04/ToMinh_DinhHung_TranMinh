#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "enemy.h"
#include <set>

class Sprite2D;
class SpriteAnimation;

//custom compare set
struct cmp {
	bool operator() (const std::shared_ptr<enemy> a,const std::shared_ptr<enemy> b) const {
		return a->Get2DPosition().y < b->Get2DPosition().y;
	}
};

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
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;               
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	//std::set<std::shared_ptr<enemy>, cmp> m_listEnemy;
	std::vector<std::shared_ptr<enemy>> m_vectorEnemy;
	std::shared_ptr<enemy> monster;
	std::shared_ptr<MouseButton> button;
	
	float time = 0.0f;
	float m_Velocity = 10.0f;

};

