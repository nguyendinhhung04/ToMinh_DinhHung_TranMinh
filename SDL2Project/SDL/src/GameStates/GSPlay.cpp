#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"





GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Cave/Background_GSPlay.tga");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(1280, 720);
	m_background->Set2DPosition(0,0);


	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	
	texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/characters/crazy.png");
	obj = std::make_shared<SpriteAnimation>( texture, 1, 1, 1, 1.00f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(100, 100);
	obj->Set2DPosition(240, 400);
	Camera::GetInstance()->SetTarget(obj);        //Set target to obj
	m_listAnimation.push_back(obj);
	

	//Player
	/*
	texture = ResourceManagers::GetInstance()->GetTexture("PlayerCharacter.tga");
	player = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	player->SetSize(350, 350);
	player->Set2DPosition(500 , 500);
	*/


	//Enemy
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("enemy1.tga");
	monster = std::make_shared<enemy>(texture, 1, 1, 1, 1.00f);
	monster->SetFlip(SDL_FLIP_HORIZONTAL);
	monster->SetSize(60, 100);
	monster->Set2DPosition(100, 100);
	monster->m_MoveSpeed = 1.80f;
	m_listEnemy.push_back(monster);

	m_KeyPress = 0;
	
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}
void GSPlay::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN )//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)                                                                                            
		{              

		case SDLK_LEFT:
			m_KeyPress |= 1;
			break;
		case SDLK_DOWN:

			m_KeyPress |= 1 << 1;
			break;
		case SDLK_RIGHT:

			m_KeyPress |= 1 << 2;
			break;
		case SDLK_UP:

			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP )//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;

			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;

			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;

			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;

			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{

	default:
		break;
	}
	// Key State event
	
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	
	for (auto it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{
			it->MoveLeft(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 2) {
			it->MoveDown(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 4) {
			it->MoveRight(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 8) {
			it->MoveUp(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 3) {
			it->MoveLeftDown(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 9) {
			it->MoveLeftUp(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 12) {
			it->MoveRightUp(deltaTime, obj->m_MoveSpeed);
		}
		else if (m_KeyPress == 6) {
			it->MoveRightDown(deltaTime, obj->m_MoveSpeed);
		}

		it->Update(deltaTime);
	}

	for (auto it : m_listEnemy)
	{
		it->MoveToCharacter(deltaTime, monster->m_MoveSpeed, obj->Get2DPosition());
		it->Update(deltaTime);
	}

	obj->Update(deltaTime);
	

	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}



void GSPlay::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	
	for (auto it : m_listEnemy)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
}