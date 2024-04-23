#include"Camera.h"
#define WIDTH_OFFSET 100
#define HEIGHT_OFFSET 100

void Camera::Init()
{
	m_ViewBox.x = (m_Target->Get2DPosition().x - SCREEN_WIDTH / 2);
	m_ViewBox.y = (m_Target->Get2DPosition().y - SCREEN_HEIDHT / 2);
}

SDL_Rect Camera::GetViewBox()
{
	return m_ViewBox;
}

Vector2 Camera::GetPosition()
{
	return m_Position;
}

void Camera::SetTarget(std::shared_ptr<SpriteAnimation> target) // Settarget for player (-> Set origin position)
{
	m_Target = target;
}

void Camera::Update(float deltaTime)
{
	if (m_Target != nullptr)
	{
		

		if (m_Target->Get2DPosition().x < m_ViewBox.x + WIDTH_OFFSET)
		{
			m_ViewBox.x -= m_ViewBox.x + WIDTH_OFFSET - m_Target->Get2DPosition().x;
		}

		else if (m_Target->Get2DPosition().x + m_Target->GetWidth() > m_ViewBox.x + SCREEN_WIDTH - WIDTH_OFFSET)
		{
			m_ViewBox.x += m_Target->Get2DPosition().x + m_Target->GetWidth() - (m_ViewBox.x + SCREEN_WIDTH - WIDTH_OFFSET);
		}
		if (m_Target->Get2DPosition().y < m_ViewBox.y + HEIGHT_OFFSET)
		{
			m_ViewBox.y -= m_ViewBox.y + HEIGHT_OFFSET - m_Target->Get2DPosition().y;
		}

		else if (m_Target->Get2DPosition().y + m_Target->GetHeight() > m_ViewBox.y + SCREEN_HEIDHT - HEIGHT_OFFSET)
		{
			m_ViewBox.y += m_Target->Get2DPosition().y + m_Target->GetHeight() - (m_ViewBox.y + SCREEN_HEIDHT - HEIGHT_OFFSET);
		}
		m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
		
		
	}
}
