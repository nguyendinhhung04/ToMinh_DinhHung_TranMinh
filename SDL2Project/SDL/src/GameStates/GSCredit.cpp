#include "GSCredit.h"
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"

GSCredit::GSCredit() {}

GSCredit::~GSCredit() {}

void GSCredit::Init() {
    // Set designed page
    auto texture = ResourceManagers::GetInstance()->GetTexture("Credit_background.png");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
    m_background->Set2DPosition(0, 0);
    m_background->SetType(DYNAMIC);

    texture = ResourceManagers::GetInstance()->GetTexture("Buttons/Large Buttons/Large Buttons/Back Button.png");
    button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    button->SetSize(180, 60);
    button->Set2DPosition(SCREEN_WIDTH - 190, 10);
    button->SetOnClick([]() {
        GameStateMachine::GetInstance()->PopState();
        });
    button->SetType(DYNAMIC);
    m_listButton.push_back(button);
}

void GSCredit::Exit() {}

void GSCredit::Pause() {}

void GSCredit::Resume() {}

void GSCredit::HandleEvents() {
    SDL_Event events;
    while (SDL_PollEvent(&events)) {
        switch (events.type) {
        case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_RETURN) {
                // Go back to the previous state
                GameStateMachine::GetInstance()->PopState();
            }
            break;
        default:
            break;
        }
    }
}

void GSCredit::HandleKeyEvents(SDL_Event& e) {}

void GSCredit::HandleTouchEvents(SDL_Event& e) 
{
    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            break;
        }
    }
}

void GSCredit::HandleMouseMoveEvents(int x, int y) {}

void GSCredit::Update(float deltaTime) {}

void GSCredit::Draw(SDL_Renderer* renderer) {

    m_background->Draw(renderer);
    for (auto it : m_listButton)
    {
        it->Draw(renderer);
    }
}
