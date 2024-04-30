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

#define INIT_HEALTHBAR_WIDTH 290
#define INIT_HEALTHBAR_HEIGHT 40

float RandomNumber()
{
	float temp1 = rand() % 2 + 1;
	float temp2;
	if (temp1 == 1)
	{
		temp2 = rand() % 151 + 1000;
	}
	else
	{
		temp2 = -(rand() % 151 + 800);
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
	op1 = -1, op2 = -1, op3 = -1;
	enemyKilled = 0;

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
	m_border->Set2DPosition(0 - (m_border->GetWidth() / 2 - m_background->GetWidth() / 2), 0 - (m_border->GetHeight() / 2 - m_background->GetHeight() / 2));
	m_border->SetType(STATIC);

	std::string fileName = "Data/update.txt";
	std::string fileName2 = "Data/updateGun.txt";
	std::string fileName3 = "Data/level.txt";
	createChooseGunButtonFromFile(fileName2, m_listUpdateButton);
	createChooseButtonFromFile(fileName, m_listUpdateButton);
	createLevelFromFile(fileName3);
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



	texture = ResourceManagers::GetInstance()->GetTexture("Menu/GrayBorder.png");
	grayBorder = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	grayBorder->Set2DPosition(15, 15);
	grayBorder->SetSize(300, 50);
	grayBorder->SetType(DYNAMIC);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu/RedBox.png");
	redBox = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	redBox->SetSize(290, 40);
	redBox->Set2DPosition( grayBorder->Get2DPosition().x + (grayBorder->GetWidth()/2 - redBox->GetWidth()/2), grayBorder->Get2DPosition().y + (grayBorder->GetHeight()/2 - redBox->GetHeight()/2));
	redBox->SetType(DYNAMIC);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu/GreenBox.png");
	greenBox = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	greenBox->SetSize(290, 40);
	greenBox->Set2DPosition(redBox->Get2DPosition().x, redBox->Get2DPosition().y);
	greenBox->SetType(DYNAMIC);

	// Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("PlayerAnimation.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 8, 3, 0.03f);
	obj->SetFlip(SDL_FLIP_NONE);      //None == right, Horizontal = left
	obj->SetSize(50, 50);
	obj->Set2DPosition(m_background->GetWidth() / 2, m_background->GetHeight() / 2);
	Camera::GetInstance()->SetTarget(obj, m_border);        //Set target to obj
	Camera::GetInstance()->Init();
	m_listAnimation.push_back(obj);
	
	//weapon	
	texture = texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/weapons/laser_pistol.png");
	weapon = std::make_shared<BaseWeapon>(texture, 1, 1, 1, 1.00f);
	weapon->SetSize(40, 40);
	weapon->Set2DPosition(obj->Get2DPosition().x + obj->GetWidth() , obj->Get2DPosition().y);
	m_vectorWeapon.push_back(weapon);


	//enemy Killed Display
	SDL_Color color = { 255,255,255 };
	m_enemyKilledDisplay = std::make_shared<Text>("Data/RobotoMono-VariableFont_wght.ttf", color);
	m_enemyKilledDisplay->Set2DPosition(grayBorder->Get2DPosition().x, grayBorder->Get2DPosition().y + grayBorder->GetHeight() + 10);
	m_enemyKilledDisplay->SetSize(180, 30);
	m_enemyKilledDisplay->LoadFromRenderText("Enemy Killed: " + std::to_string(enemyKilled));

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

	for (auto button : m_listUpdateButton)
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
	if (obj->isGotHit == false)
	{
		obj->m_spriteRow = 2;
	}
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

		for (auto it : m_listUpdateButton)
		{
			it->Update(deltaTime);
		}
		for (auto it : m_listAnimation)
		{
			if (m_KeyPress == 1)
			{
				it->MoveLeft(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 2) {
				it->MoveDown(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 4) {
				it->MoveRight(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 8) {
				it->MoveUp(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 3) {
				it->MoveLeftDown(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 9) {
				it->MoveLeftUp(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 12) {
				it->MoveRightUp(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			else if (m_KeyPress == 6) {
				it->MoveRightDown(deltaTime, obj->m_MoveSpeed);
				if (obj->isGotHit == false)
				{
					obj->m_spriteRow = 1;
				}
			}
			it->Update(deltaTime);
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



		
		for (int i = 0; i < m_vectorWeapon.size(); i++)
		{
			if (i == 0) m_vectorWeapon[i]->Set2DPosition(obj->Get2DPosition().x - 10, obj->Get2DPosition().y - 25);
			else if (i == 1) m_vectorWeapon[i]->Set2DPosition(obj->Get2DPosition().x + obj->GetWidth() - 5, obj->Get2DPosition().y - 25);
			else if (i == 2) m_vectorWeapon[i]->Set2DPosition(obj->Get2DPosition().x - 10, obj->Get2DPosition().y + obj->GetHeight() / 2);
			else if (i == 4) m_vectorWeapon[i]->Set2DPosition(obj->Get2DPosition().x - 10 + obj->GetWidth(), obj->Get2DPosition().y + obj->GetHeight()/ 2 - 25);
			else if (i == 5) i = 5; // sua cho nay
			else if (i == 6) i = 6; // sua cho nay
			//m_vectorWeapon[i]->Set2DPosition(obj->Get2DPosition().x + 35 * i, obj->Get2DPosition().y - 25);
			if (m_vectorWeapon[i]->CheckEnemyInRange(m_vectorEnemyS[m_level], obj->Get2DPosition()))
			{
				bullet = m_vectorWeapon[i]->Fire(deltaTime, m_vectorEnemyS[m_level]);
				if(bullet)
				{
					m_vectorBullet.push_back(bullet);
					
				}
			}
			m_vectorWeapon[i]->Update(deltaTime);
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

					auto texture = ResourceManagers::GetInstance()->GetTexture("BulletHitEnemy.png");
					boom = std::make_shared<SpriteAnimation>(texture, 1, 7, 1, 0.03f);
					boom->SetFlip(SDL_FLIP_NONE);     
					boom->SetSize(70, 70);
					boom->Set2DPosition((*it2)->Get2DPosition().x + (*it2)->GetWidth() / 2- boom->GetWidth()/2, (*it2)->Get2DPosition().y + (*it2)->GetHeight() / 2 - boom->GetHeight()/2);
					std::pair< std::shared_ptr<SpriteAnimation>, float >  temp;
					temp.first = boom;
					temp.second = 0.00f;
					m_vectorBoom.push_back(temp);
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
				enemyKilled += 1;
			}
			else
			{
				(*it)->Update(deltaTime);
				++it;
				
			}

		}
		
		if (m_vectorEnemyS[m_level].size() == 0)
		{
			m_isPlaying = false;
			m_isUpdate = true;
			if (op1 == -1 && op2 == -1 && op3 == -1)
			{
				op1 = rand() % m_listUpdateButton.size();
				do
				{
					op2 = rand() % m_listUpdateButton.size();
				} while (op2 == op1);
				do
				{
					op3 = rand() % m_listUpdateButton.size();
				} while (op3 == op1 || op3 == op2);
			}
			m_level++;
		}
	}

	if (m_vectorBoom.size() > 0)
	{
		for (auto it = m_vectorBoom.begin(); it != m_vectorBoom.end();)
		{
			(*it).first->Update(deltaTime);
			(*it).second += deltaTime;
			if ((*it).second > 0.21f)
			{
				(*it) = std::make_pair(nullptr, 0);   //giai phong bo nho cho pair
				it = m_vectorBoom.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	greenBox->SetSize(INIT_HEALTHBAR_WIDTH * (obj->getHP() / 100), INIT_HEALTHBAR_HEIGHT);

	m_enemyKilledDisplay->LoadFromRenderText("Enemy Killed: " + std::to_string(enemyKilled));

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

	if (m_vectorBoom.size() > 0)
	{
		for (auto it : m_vectorBoom)
		{
			it.first->Draw(renderer);
		}
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
	grayBorder->Draw(renderer);
	redBox->Draw(renderer);
	greenBox->Draw(renderer);
	m_enemyKilledDisplay->Draw(renderer);


	if (m_isUpdate)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
		SDL_RenderFillRect(renderer, &m_darkOverlay);
		//rand 3 num

		auto b1 = m_listUpdateButton[op1];
		b1->Set2DPosition(SCREEN_WIDTH / 2 - 550, SCREEN_HEIDHT / 2);
		b1->Draw(renderer);
		auto b2 = m_listUpdateButton[op2];
		b2->Set2DPosition(SCREEN_WIDTH / 2 - 150, SCREEN_HEIDHT / 2);
		b2->Draw(renderer);
		auto b3 = m_listUpdateButton[op3];
		b3->Set2DPosition(SCREEN_WIDTH / 2 + 250, SCREEN_HEIDHT / 2);
		b3->Draw(renderer);

		grayBorder->Draw(renderer);
		redBox->Draw(renderer);
		greenBox->Draw(renderer);
		m_enemyKilledDisplay->Draw(renderer);

	}
}





void GSPlay::createChooseButtonFromFile(std::string& filename, std::vector<std::shared_ptr<MouseButton>>& buttonList)
{
	std::ifstream file(filename);
	std::string texturePath;
	std::string bonus;

	std::shared_ptr<MouseButton> chooseButton;
	while (std::getline(file, texturePath) && std::getline(file, bonus))
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture(texturePath);
		std::istringstream iss(bonus); // Construct istringstream with 'bonus'
		float hp, damage, speed;
		if (iss >> hp >> damage >> speed)
		{
			chooseButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
			chooseButton->SetSize(300, 300);
			chooseButton->Set2DPosition(0, 0);
			chooseButton->SetType(DYNAMIC);
			chooseButton->SetOnClick([this, hp,damage,speed]() {
				if (m_isUpdate == true)
				{
					m_isPlaying = !m_isPlaying;
					m_isUpdate = false;
					op1 = -1;
					op2 = -1;
					op3 = -1;
					obj->setHP(obj->getHP() + hp);
					obj->m_MoveSpeed += speed;
					for (auto it : m_vectorWeapon)
					{
						it->setDamage(it->getDamage() + damage);
					}
					
				}
				});

			buttonList.push_back(chooseButton);
			chooseButton.reset();
		}
	}
}



void GSPlay::createChooseGunButtonFromFile(std::string& filename, std::vector<std::shared_ptr<MouseButton>>& buttonList)
{
	std::ifstream file(filename);
	std::string texturePath;  
	std::string textureGunPath; 
	std::string bulletPath; 
	std::string damage; 
	std::shared_ptr<MouseButton> chooseButton;
	while (std::getline(file, texturePath) && std::getline(file, textureGunPath) && std::getline(file,bulletPath) && std::getline(file, damage))
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture(texturePath);
		std::istringstream iss(damage); // Construct istringstream with 'bonus'
		float damage,speed_rate,range;
		if (iss >> damage >> speed_rate >> range)
		{
			chooseButton = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
			chooseButton->SetSize(300, 300);
			chooseButton->Set2DPosition(0, 0);
			chooseButton->SetType(DYNAMIC);
			chooseButton->SetOnClick([this, damage, speed_rate, range , textureGunPath,bulletPath]() {
				if (m_isUpdate == true)
				{
					m_isPlaying = !m_isPlaying;
					m_isUpdate = false;
					op1 = -1;
					op2 = -1;
					op3 = -1;
					if (gun_slot <= 5)
					{
						auto textureGun = ResourceManagers::GetInstance()->GetTexture(textureGunPath);
						auto addWeapon = std::make_shared<BaseWeapon>(textureGun, 1, 1, 1, 1.00f, bulletPath, damage, speed_rate, range);
						addWeapon->SetSize(40, 40);
						m_vectorWeapon.push_back(addWeapon);
						gun_slot++;
					}
				}
				});

			buttonList.push_back(chooseButton);
			chooseButton.reset();
		}
	}
}


void GSPlay::createLevelFromFile(std::string& filename)
{
	std::ifstream file(filename);
	std::string textureEnemyPath;
	std::string infomation;
	while (std::getline(file, textureEnemyPath) && std::getline(file, infomation))
	{
		auto textureEnemy = ResourceManagers::GetInstance()->GetTexture(textureEnemyPath);
		std::istringstream iss(infomation); // Construct istringstream with 'bonus'
		float number,hp,damage,speed;
		if (iss >> number >> hp >> damage >> speed)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			for (int i = 0; i <= number; i++)
			{
				monster = std::make_shared<enemy>(textureEnemy, 1, 8, 1, 0.07f, hp/*enemy HP*/, damage/*enemy power*/, speed /*enemy speed*/);
				monster->SetFlip(SDL_FLIP_NONE);
				monster->SetSize(60, 60);
				float temp1 = RandomNumber();
				float temp2 = RandomNumber();
				monster->Set2DPosition(temp1, temp2);
				m_vectorEnemy.push_back(monster);
			}
			m_vectorEnemyS.push_back(m_vectorEnemy);
			m_vectorEnemy.clear();
		}
	}
}


int GSPlay :: getRandomNumber(int low, int high) {
	return low + rand() % (high - low + 1);
}

void GSPlay::generateUniqueRandomNumbers(int n,int &x,int &y,int &z)
{
	std::vector<int> numbers;
	// Fill the vector with numbers from 1 to n
	for (int i = 0; i < n; ++i) {
		numbers.push_back(i);
	}
	
	for (int i = 0; i < 3; ++i) {
		int j = getRandomNumber(0, n - 1);
		std::swap(numbers[i], numbers[j]);
	}
	// Return the first three elements
	x = numbers[0];
	y = numbers[1];
	z = numbers[2];
}


