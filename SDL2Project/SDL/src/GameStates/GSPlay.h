#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "enemy.h"
#include "BaseWeapon.h"
#include "TextTimer.h"





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
	void createChooseButtonFromFile(std::string& filename, std::vector<std::shared_ptr<MouseButton>>& buttonList);
	void createChooseGunButtonFromFile(std::string& filename, std::vector<std::shared_ptr<MouseButton>>& buttonList);
	void createLevelFromFile(std::string& filename);
	int getRandomNumber(int low, int high);
	void generateUniqueRandomNumbers(int n,int &x,int &y,int &z);
	void DrawPauseScreen(SDL_Renderer* renderer);

	int m_level = 0;
	int gun_slot = 0;
	bool m_isUpdate = false;
	bool m_isChooseUpdate = false;

	std::shared_ptr<Sprite2D>	m_background;

	std::vector<std::shared_ptr<Sprite2D>> m_listUpdate;
	std::shared_ptr<Sprite2D>	m_update;
	//std::shared_ptr<Text>		m_score;
	std::shared_ptr<MouseButton> update_button;
	std::vector<std::shared_ptr<MouseButton>>	m_listUpdateButton;

	std::shared_ptr<MouseButton> gun_update_button;
	std::vector<std::shared_ptr<MouseButton>>	m_listGunUpdateButton;

	std::list<std::shared_ptr<MouseButton>>	m_listButton;               
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	//std::list<std::shared_ptr<enemy>> m_listEnemy;
	std::vector<std::vector<std::shared_ptr<enemy>>> m_vectorEnemyS;
	std::vector<std::shared_ptr<enemy>> m_vectorEnemy;
	std::shared_ptr<enemy> monster;

	std::shared_ptr<MouseButton> button;

	std::shared_ptr<Sprite2D> m_border;

	std::shared_ptr<BaseWeapon> weapon;
	std::vector<std::shared_ptr<BaseWeapon>> m_vectorWeapon;

	std::shared_ptr<Bullet> bullet;
	std::vector<std::shared_ptr<Bullet>> m_vectorBullet;

	std::shared_ptr<Sprite2D> grayBorder;
	std::shared_ptr<Sprite2D> redBox;
	std::shared_ptr<Sprite2D> greenBox;

	std::shared_ptr<MouseButton> pause_button;
	std::shared_ptr<MouseButton> pause_restart_button;
	std::shared_ptr<MouseButton> pause_option_button;
	std::vector<std::shared_ptr<MouseButton>>	m_listPauseButton;

	std::shared_ptr<SpriteAnimation> boom;
	//std::vector<std::shared_ptr<SpriteAnimation>> m_vectorBoom;
	std::vector<std::pair<std::shared_ptr<SpriteAnimation>, float>> m_vectorBoom;
	std::shared_ptr<TextTimer> m_timer;

	int op1, op2, op3;


	SDL_Rect m_darkOverlay;
	SDL_Rect m_HealthBarHitEffect;

	std::shared_ptr<Sound>					m_Sound;

	
	float time = 0.0f;
	float m_Velocity = 10.0f;

	bool m_isPlaying;


};

