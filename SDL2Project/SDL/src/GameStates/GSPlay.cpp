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
	/*
	texture = ResourceManagers::GetInstance()->GetTexture("PlayerCharacter.tga");
	obj = std::make_shared<SpriteAnimation>( texture, 2, 9, 6, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(40, 50);
	obj->Set2DPosition(240, 400);
	Camera::GetInstance()->SetTarget(obj);        //Set target to obj
	m_listAnimation.push_back(obj);
	*/

	//Player
	texture = ResourceManagers::GetInstance()->GetTexture("PlayerCharacter.tga");
	player = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	player->SetSize(350, 350);
	player->Set2DPosition(500 , 500);


	//Enemy
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("Brotato.tga");
	monster = std::make_shared<enemy>(texture, 2, 9, 6, 0.2f);
	monster->SetFlip(SDL_FLIP_HORIZONTAL);
	monster->SetSize(60, 100);
	monster->Set2DPosition(240, 500);
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
	
	if (m_KeyPress == 1)
	{
		player->MoveLeft(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 2) {
		player->MoveDown(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 4) {
		player->MoveRight(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 8) {
		player->MoveUp(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 3) {
		player->MoveLeftDown(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 9) {
		player->MoveLeftUp(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 12) {
		player->MoveRightUp(deltaTime, player->m_MoveSpeed);
	}
	else if (m_KeyPress == 6) {
		player->MoveRightDown(deltaTime, player->m_MoveSpeed);
	}

	for (auto it : m_listEnemy)
	{
		it->MoveToCharacter(deltaTime, monster->m_MoveSpeed, player->Get2DPosition());
		monster->Update(deltaTime);
	}

	player->Update(deltaTime);
	printf("%f %f %f\_____", player->Get2DPosition().x, player->Get2DPosition().y, player->Get2DPosition().z);
	printf("%f %f %f\n", m_background->Get2DPosition().x, m_background->Get2DPosition().y, m_background->Get2DPosition().z);

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
	player->Draw(renderer);
	for (auto it : m_listEnemy)
	{
		it->Draw(renderer);
	}
}