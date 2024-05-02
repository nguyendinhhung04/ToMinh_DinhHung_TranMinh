#include "GSLose.h"

GSLose::GSLose() : GameStateBase(StateType::STATE_LOSE),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{})
{
}

//GSLose::GSLose()
//{
//}

GSLose::~GSLose()
{
}

void GSLose::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Game_over.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);
	m_background->SetType(DYNAMIC);



}

void GSLose::Exit()
{
}

void GSLose::Pause()
{

}

void GSLose::Resume()
{

}


void GSLose::HandleEvents()
{
}

void GSLose::HandleKeyEvents(SDL_Event& e)
{
}

void GSLose::HandleTouchEvents(SDL_Event& e)
{

	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSLose::HandleMouseMoveEvents(int x, int y)
{

}


void GSLose::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSLose::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}