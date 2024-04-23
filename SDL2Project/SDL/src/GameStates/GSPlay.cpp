#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"

#include "GameStateMachine.h"
#include "KeyState.h"

#include <cstdlib> 
#include <ctime>   


float RandomNumber()
{
	float temp1 = rand() % 2 + 1;
	float temp2;
	if (temp1 == 1)
	{
		temp2 = rand() % 401 + 1600;
	}
	else
	{
		temp2 = -(rand() % 401 + 1600);
	}
	return temp2;
}



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_isPlaying = true;


	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Cave/Background_GSPlay.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(2000, 1114);
	m_background->Set2DPosition(0, 0);
	m_background->SetType(STATIC);
	texture = ResourceManagers::GetInstance()->GetTexture("Border.png");
	m_border = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_border->SetSize(2100, 1169.7);
	m_border->Set2DPosition(0-(m_border->GetWidth()/2 - m_background->GetWidth()/2), 0 - (m_border->GetHeight()/2 - m_background->GetHeight()/2));
	m_background->SetType(STATIC);


	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("Buttons/Square Buttons/Square Buttons/Pause Square Button.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 60, 10);
	button->SetType(DYNAMIC);
	button->SetOnClick([this]() {
		m_isPlaying = !m_isPlaying;
		if (m_isPlaying)
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("Buttons/Square Buttons/Square Buttons/Pause Square Button.png"));
		}
		else
		{
			button->SetTexture(ResourceManagers::GetInstance()->GetTexture("Buttons/Square Buttons/Square Buttons/Play Square Button.png"));
		}

		});
	m_listButton.push_back(button);

	// Animation 

	texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/characters/crazy.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 1, 1, 1.00f);
	//obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetFlip(SDL_FLIP_NONE);      //None == right, Horizontal = left
	obj->SetSize(50, 50);
	obj->Set2DPosition(m_background->GetWidth()/2, m_background->GetHeight()/2);
	Camera::GetInstance()->SetTarget(obj);        //Set target to obj
	Camera::GetInstance()->Init();
	m_listAnimation.push_back(obj);
	
	//weapon	
	texture = texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/weapons/laser_pistol.png");
	weapon = std::make_shared<BaseWeapon>(texture, 1, 1, 1, 1.00f);
	weapon->SetSize(40, 40);
	weapon->Set2DPosition(obj->Get2DPosition().x + obj->GetWidth() , obj->Get2DPosition().y);
	m_vectorWeapon.push_back(weapon);

	////Enemy
	////lv1 init
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("enemy1.tga");
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i <= 5; i++)
	{
		monster = std::make_shared<enemy>(texture2, 1, 1, 1, 1.00f,10.0/*enemy HP*/, 10.0/*enemy power*/, obj->GetSpeed() * 0.500 /*enemy speed*/);
		monster->SetFlip(SDL_FLIP_NONE);
		monster->SetSize(60, 60);
		float temp1 = RandomNumber();
		float temp2 = RandomNumber();
		printf("%f____%f", temp1, temp2);
		monster->Set2DPosition(temp1, temp2);
		m_vectorEnemy.push_back(monster);
	}
	m_vectorEnemyS.push_back(m_vectorEnemy);
	m_vectorEnemy.clear();
	//lv2 init
	texture2 = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/enemies/5.png");
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i <= 8; i++)
	{
		monster = std::make_shared<enemy>(texture2, 1, 1, 1, 1.00f, 100.0, 20.0,250);
		monster->SetFlip(SDL_FLIP_NONE);
		monster->SetSize(60, 60);
		float temp1 = RandomNumber();
		float temp2 = RandomNumber();
		printf("%f____%f", temp1, temp2);
		monster->Set2DPosition(temp1, temp2);
		m_vectorEnemy.push_back(monster);
	}
	m_vectorEnemyS.push_back(m_vectorEnemy);


	





	m_KeyPress = 0;

	m_darkOverlay = { 0,0,SCREEN_WIDTH, SCREEN_HEIDHT };



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
	if (e.type == SDL_KEYDOWN)//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
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
	else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
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
	if (m_isPlaying)
	{
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
			printf("%f___%f\n", it->Get2DPosition().x, it->Get2DPosition().y);
		}



		

		//sort the vector
		if (m_vectorEnemyS[m_level].size() > 1)
		{
			for (auto it = m_vectorEnemyS[m_level].begin(); it != m_vectorEnemyS[m_level].end() - 1; ++it)
			{
				for (auto temp = it; temp != m_vectorEnemyS[m_level].end() - 1; ++temp)
				{
					if ((*temp)->Get2DPosition().y > (*(temp + 1))->Get2DPosition().y)
					{
						std::shared_ptr<enemy> temp_monster = *temp;
						*temp = *(temp + 1);
						*(temp + 1) = temp_monster;
					}
				}
			}
		}



		
		for (auto it : m_vectorWeapon)
		{
			it->Set2DPosition(obj->Get2DPosition().x +35, obj->Get2DPosition().y - 25);
			if (it->CheckEnemyInRange(m_vectorEnemyS[m_level], obj->Get2DPosition()))
			{
				bullet =  it->Fire( deltaTime, m_vectorEnemyS[m_level]);
				if(bullet)
				{
					m_vectorBullet.push_back(bullet);
					
				}
			}
			it->Update(deltaTime);
		}
		
		
		for (auto it = m_vectorBullet.begin(); it!=m_vectorBullet.end(); )
		{
			(*it)->MoveToTarget(deltaTime);
			if ((*it)->Get2DPosition().x > 2000 || (*it)->Get2DPosition().y > 1500) 
			{
				(*it).reset();
				it = m_vectorBullet.erase(it);
			}
			else
			{
				(*it)->Update(deltaTime);
				++it;
			}
		}
		
		for (auto it = m_vectorEnemyS[m_level].begin(); it != m_vectorEnemyS[m_level].end()&& m_vectorEnemyS[m_level].size()>0; )
		{
			(*it)->MoveToCharacterX(deltaTime, (*it)->getSpeed(), obj->Get2DPosition(), m_vectorEnemyS[m_level]);
			(*it)->MoveToCharacterY(deltaTime, (*it)->getSpeed(), obj->Get2DPosition(), m_vectorEnemyS[m_level]);
			if (obj->CheckCollision((*it)->Get2DPosition(), (*it)->GetWidth(), (*it)->GetHeight()))
			{
				obj->minusHP((*it)->getPower(), deltaTime);
			}
			for (auto it2 = m_vectorBullet.begin(); it2 != m_vectorBullet.end() && m_vectorBullet.size()>0 ; )
			{
				if ((*it2)->CheckCollision((*it)->Get2DPosition(), (*it)->GetWidth(), (*it)->GetHeight()) == true)
		 		{
					(*it)->Damaged((*it2)->GetDamageAmount());
					(*it2).reset();
					it2 = m_vectorBullet.erase(it2);
				}
				else
				{
					++it2;
				}
			}
			
			if ((*it)->GetHP() <= 0) 
			{
				(*it).reset();
				it = m_vectorEnemyS[m_level].erase(it);
			}
			else
			{
				(*it)->Update(deltaTime);
				++it;
				
			}

		}
		
		if (m_vectorEnemyS[m_level].size() == 0)
		{
			if (m_level < 1)
			{
				m_level++;
			}
		}
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
}



void GSPlay::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);
	//m_score->Draw();

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	/*
	//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		if (it->getHP() > 0) it->Draw(renderer);
	}
	*/
	

	


	bool m_alreadyDrawPlayer = false;
	if (m_vectorEnemyS[m_level].size() >= 1)
	{
		for (auto it : m_vectorEnemyS[m_level])
		{
			if (m_alreadyDrawPlayer == false)
			{
				if (it->Get2DPosition().y > obj->Get2DPosition().y)
				{
					if (obj->getHP() > 0)
					{
						obj->Draw(renderer);
						m_alreadyDrawPlayer = true;
					}
				}
			}
			it->Draw(renderer);
		}
	}
	if (m_alreadyDrawPlayer == false)
	{
		if (obj->getHP() > 0)
		{
			obj->Draw(renderer);
			m_alreadyDrawPlayer = true;
		}
	}

	for (auto it : m_vectorBullet)
	{
		it->Draw(renderer);
	}

	for (auto it : m_vectorWeapon)
	{
		it->Draw(renderer);
	}
	m_border->Draw(renderer);

	if (!m_isPlaying)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);

		SDL_RenderFillRect(renderer, &m_darkOverlay);
		for (auto it : m_listButton)
		{
			it->Draw(renderer);
		}
	}
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
}