#include "GSPause.h"


GSPause::GSPause() : GameStateBase(StateType::STATE_PAUSE),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Cave/Background_GSPlay.tga");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// Resume button
	texture = ResourceManagers::GetInstance()->GetTexture("Buttons/Large Buttons/Large Buttons/Resume button.png");
	std::shared_ptr<MouseButton> btnResume = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnResume->SetSize(270, 80);
	btnResume->Set2DPosition((SCREEN_WIDTH - btnResume->GetWidth()) / 2, (SCREEN_HEIDHT - btnResume->GetHeight()) / 2 + 120);
	btnResume->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnResume);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Buttons/Large Buttons/Large Buttons/Menu button.png");
	std::shared_ptr<MouseButton> btnMenu = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnMenu = std::make_shared<MouseButton>(texture);
	btnMenu->SetSize(270, 80);
	btnMenu->Set2DPosition((SCREEN_WIDTH - btnMenu->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 170);
	btnMenu->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnMenu);


}

void GSPause::Exit()
{
}


void GSPause::Pause()
{

}

void GSPause::Resume()
{
}


void GSPause::HandleEvents()
{
}

void GSPause::HandleKeyEvents(SDL_Event& e)
{
}

void GSPause::HandleTouchEvents(SDL_Event& e)
{

	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSPause::HandleMouseMoveEvents(int x, int y)
{

}

void GSPause::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPause::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}
