#include "GSOption.h"
#include "GameStateMachine.h"
#include "GameManager/ResourceManagers.h"

GSOption::GSOption() {}

GSOption::~GSOption() {}

void GSOption::Init() {



    // Load background texture
    auto texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/splash_art_no_logo.png");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
    m_background->Set2DPosition(0, 0);

    // Load volume bar texture
    texture = ResourceManagers::GetInstance()->GetTexture("volume_bar.png");
    m_volumeBar = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_volumeBar->SetSize(400, 50);
    m_volumeBar->Set2DPosition((SCREEN_WIDTH - m_volumeBar->GetWidth()) / 2, (SCREEN_HEIDHT - m_volumeBar->GetHeight()) / 2);

    // Load volume knob texture
    texture = ResourceManagers::GetInstance()->GetTexture("volume_knob.png");
    m_volumeKnob = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_volumeKnob->SetSize(30, 30);
    m_volumeKnob->Set2DPosition((SCREEN_WIDTH - m_volumeBar->GetWidth()) / 2, (SCREEN_HEIDHT - m_volumeKnob->GetHeight()) / 2);

    // Initialize volume level
    m_volumeLevel = 50; // Assuming 50% initial volume

    texture = ResourceManagers::GetInstance()->GetTexture("Buttons/Large Buttons/Large Buttons/Back Button.png");
    button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    button->SetSize(180, 60);
    button->Set2DPosition(SCREEN_WIDTH - 190, 10);
    button->SetOnClick([]() {
        GameStateMachine::GetInstance()->PopState();
        });
    m_listButton.push_back(button);


    m_textColor = { 255, 255, 0 };
    m_text = std::make_shared<Text>("Data/BMYEONSUNG_ttf.ttf", m_textColor);
    m_text->SetSize(300, 50);
    m_text->Set2DPosition((SCREEN_WIDTH - m_text->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 300);
    m_text->LoadFromRenderText("Volume Adjustment");


}

void GSOption::Exit() {}

void GSOption::Pause() {}

void GSOption::Resume() {}

void GSOption::HandleEvents() {}

void GSOption::HandleKeyEvents(SDL_Event& e) {}

void GSOption::HandleTouchEvents(SDL_Event& e) {
    // Handle volume adjustment by dragging volume knob
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Check if mouse click is within the volume knob bounds
        if (mouseX >= m_volumeKnob->Get2DPosition().x &&
            mouseX <= m_volumeKnob->Get2DPosition().x + m_volumeKnob->GetWidth() &&
            mouseY >= m_volumeKnob->Get2DPosition().y &&
            mouseY <= m_volumeKnob->Get2DPosition().y + m_volumeKnob->GetHeight()) {
            m_isDragging = true;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        m_isDragging = false;
    }
    else if (e.type == SDL_MOUSEMOTION && m_isDragging) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Clamp volume knob position within volume bar bounds
        float newX = std::min(std::max(mouseX - m_volumeKnob->GetWidth() / 2.0f, m_volumeBar->Get2DPosition().x), m_volumeBar->Get2DPosition().x + m_volumeBar->GetWidth() - m_volumeKnob->GetWidth());
        m_volumeKnob->Set2DPosition(newX, m_volumeBar->Get2DPosition().y + m_volumeBar->GetHeight() / 2 - m_volumeKnob->GetHeight() / 2);

        // Update volume level based on knob position
        m_volumeLevel = static_cast<int>((newX - m_volumeBar->Get2DPosition().x) / m_volumeBar->GetWidth() * 100);
    }

    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            break;
        }
    }
}

void GSOption::HandleMouseMoveEvents(int x, int y) {}

void GSOption::Update(float deltaTime) {}

void GSOption::Draw(SDL_Renderer* renderer) {

    // Draw background
    m_background->Draw(renderer);

    m_text->Draw(renderer);

    // Draw volume bar
    m_volumeBar->Draw(renderer);

    // Draw volume knob
    m_volumeKnob->Draw(renderer);

    for (auto it : m_listButton)
    {
	    it->Draw(renderer);
    }
 

    // Display volume level
    // std::string volumeText = "Volume: " + std::to_string(m_volumeLevel) + "%";
    // m_text->LoadFromRenderText(volumeText);
}
