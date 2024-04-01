#include "GSIntro.h"
#include "GameManager/ResourceManagers.h"
#include "GameObject/Define.h"
GSIntro::GSIntro() : GameStateBase(StateType::STATE_INTRO), m_time(0.0f)
{
}


GSIntro::~GSIntro()
{
}

void GSIntro::Init()
{
	printf("Hello");
	auto texture = ResourceManagers::GetInstance()->GetTexture("peter.tga");  //Create a image tga instance
	m_logo = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);   //Make pointer point to it
	m_logo->SetSize(800/2, 451/2);   //change the size 
	m_logo->Set2DPosition((float)(SCREEN_WIDTH - m_logo->GetWidth())/2 , (float)(SCREEN_HEIDHT - m_logo->GetHeight())/2);
	//set the position (in this case the logo is at the center of the screen)
	//SREEN Width, height is the size of the window
	//m_logo is the shared-pointer to the logo instance 
	//By Using Getwidth and GetHeight func to take the size of the logo
}

void GSIntro::Exit()
{
}


void GSIntro::Pause()
{
}

void GSIntro::Resume()
{

}


void GSIntro::HandleEvents()
{
}

void GSIntro::HandleKeyEvents(SDL_Event& e)
{
}

void GSIntro::HandleTouchEvents(SDL_Event& e)
{
}

void GSIntro::HandleMouseMoveEvents(int x, int y)
{
}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.5f)
	{
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		m_time = 0;
	}
}

void GSIntro::Draw(SDL_Renderer* renderer)
{
	m_logo->Draw(renderer);
}
