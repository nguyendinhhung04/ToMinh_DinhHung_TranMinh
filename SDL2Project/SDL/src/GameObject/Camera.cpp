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

void Camera::SetTarget(std::shared_ptr<SpriteAnimation> target, std::shared_ptr<Sprite2D> map) // Settarget for player (-> Set origin position)
{
	m_Target = target;
	m_map = map;
}

void Camera::SetViewBox(float x, float y)
{
	m_ViewBox.x = x;
	m_ViewBox.y = y;
}



void Camera::Update(float deltaTime)
{
	if (m_Target != nullptr && m_map!=nullptr)
	{	
		float lastPosX = m_Position.x;
		float lastPosY = m_Position.y;
		m_ViewBox.x = (m_Target->Get2DPosition().x - SCREEN_WIDTH / 2);
		m_ViewBox.y = (m_Target->Get2DPosition().y - SCREEN_HEIDHT / 2);
		
		if (m_ViewBox.x < m_map->Get2DPosition().x || m_ViewBox.x + m_ViewBox.w > m_map->Get2DPosition().x + m_map->GetWidth())
		{
			m_ViewBox.x = lastPosX;
		}
		if (m_ViewBox.y < m_map->Get2DPosition().y || m_ViewBox.y + m_ViewBox.h > m_map->Get2DPosition().y + m_map->GetHeight())
		{
			m_ViewBox.y = lastPosY;
		}

		//if (m_Target->Get2DPosition().x < m_ViewBox.x + WIDTH_OFFSET)
		//{
		//	m_ViewBox.x -= m_ViewBox.x + WIDTH_OFFSET - m_Target->Get2DPosition().x;
		//}

		//else if (m_Target->Get2DPosition().x + m_Target->GetWidth() > m_ViewBox.x + SCREEN_WIDTH - WIDTH_OFFSET)
		//{
		//	m_ViewBox.x += m_Target->Get2DPosition().x + m_Target->GetWidth() - (m_ViewBox.x + SCREEN_WIDTH - WIDTH_OFFSET);
		//}
		//if (m_Target->Get2DPosition().y < m_ViewBox.y + HEIGHT_OFFSET)
		//{
		//	m_ViewBox.y -= m_ViewBox.y + HEIGHT_OFFSET - m_Target->Get2DPosition().y;
		//}

		//else if (m_Target->Get2DPosition().y + m_Target->GetHeight() > m_ViewBox.y + SCREEN_HEIDHT - HEIGHT_OFFSET)
		//{
		//	m_ViewBox.y += m_Target->Get2DPosition().y + m_Target->GetHeight() - (m_ViewBox.y + SCREEN_HEIDHT - HEIGHT_OFFSET);
		//}


		m_Position = Vector2(m_ViewBox.x, m_ViewBox.y);
		
		
	}
}
