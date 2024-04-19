#include "Sprite2D.h"
#include "TextureManager.h"
//Sprite2D::Sprite2D()
//{
//	Init();
//}

Sprite2D::Sprite2D(std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip)
	:BaseObject(texture), m_iWidth(100), m_iHeight(50), m_type(SpriteType::DYNAMIC)
{
	m_flip = flip;
	m_MoveSpeed = (float)(70);
	Init();
	
}

void Sprite2D::Init()
{
	// Init Camera
}

SpriteType Sprite2D::GetType()
{
	return m_type;
}

void Sprite2D::SetType(SpriteType type)
{
	m_type = type;
}

void Sprite2D::Draw(SDL_Renderer * renderer)
{
	//Get2DPosition();
	if (m_pTexture != nullptr)
	{
		if (GetType() == DYNAMIC) 
		{
			m_pTexture->Render(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
		}
		else
		{
			m_pTexture->RenderRelativeToCamera(m_position.x, m_position.y, m_iWidth, m_iHeight, m_angle, m_flip);
		}
		
	}
	
}

void Sprite2D::Update(float deltatime)
{
}

void Sprite2D::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}



Vector3 Sprite2D::Get2DPosition()
{
	return Vector3(m_position.x, m_position.y, 0.0f);
}

void Sprite2D::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Sprite2D::GetWidth()
{
	return m_iWidth;
}

int Sprite2D::GetHeight()
{
	return m_iHeight;
}

void Sprite2D::SetRotation(double angle)
{
	m_angle = angle;
}

void Sprite2D::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}


void Sprite2D::MoveLeft(float deltaTime, float speed)
{
	printf("MoveLeft");
	m_position.x -= speed * deltaTime;
}

void Sprite2D::MoveRight(float deltaTime, float speed)
{
	printf("MoveRight");
	m_position.x += speed * deltaTime;
}
void Sprite2D::MoveUp(float deltaTime, float speed)
{
	printf("MoveUp");
	m_position.y -= speed * deltaTime;
}
void Sprite2D::MoveDown(float deltaTime, float speed)
{
	printf("MoveDown");
	m_position.y += speed * deltaTime;
}

void Sprite2D::MoveLeftDown(float deltaTime, float speed)
{
	m_position.x -= speed * deltaTime;
	m_position.y += speed * deltaTime;
}

void Sprite2D::MoveLeftUp(float deltaTime, float speed)
{
	m_position.x -= speed * deltaTime;
	m_position.y -= speed * deltaTime;
}

void Sprite2D::MoveRightUp(float deltaTime, float speed)
{
	m_position.x += speed * deltaTime;
	m_position.y -= speed * deltaTime;
}


void Sprite2D::MoveRightDown(float deltaTime, float speed)
{
	m_position.x += speed * deltaTime;
	m_position.y += speed * deltaTime;
}

