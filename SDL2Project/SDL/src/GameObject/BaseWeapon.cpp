#include "BaseWeapon.h"
#include "TextureManager.h"
#include <cmath>
#define INITIAL_RANGE 700
#define INITIAL_FIRESPEED 1
BaseWeapon::BaseWeapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_MoveSpeed = (float)(250);
	m_rotationDirection = true;           //True == Right,  false == left
	m_pTexture = texture;
	m_spriteRow = spriteRow;
	m_frameCount = frameCount;
	m_numAction = numAction;
	//m_animSpeed = animSpeed;
	m_frameTime = frameTime;
	//m_flip = flip;
	m_currentFrame = 0;
	m_currentTicks = 0;
	m_lastUpdate = SDL_GetTicks();
	Init();
	m_timeSinceLastFire = 0;
	m_fireSpeed = INITIAL_FIRESPEED;
	m_range = INITIAL_RANGE;
	BulletOfWeapon = NULL;
}

BaseWeapon::~BaseWeapon()
{

}

void BaseWeapon::Init()
{

}

void BaseWeapon::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}



void BaseWeapon::Update(float deltatime)
{
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount) {
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

void BaseWeapon::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void BaseWeapon::SetRotation(double angle)
{
	m_angle = angle;
}

void BaseWeapon::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 BaseWeapon::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void BaseWeapon::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int BaseWeapon::GetWidth()
{
	return m_iWidth;
}

int BaseWeapon::GetHeight()
{
	return m_iHeight;
}


void BaseWeapon::Flip(bool targetDir)
{
	if (targetDir != m_rotationDirection)
	{
		m_rotationDirection = !m_rotationDirection;
		if (m_rotationDirection == true) {
			SetFlip(SDL_FLIP_NONE);
		}
		else {
			SetFlip(SDL_FLIP_HORIZONTAL);
		}
	}
}



//range
bool BaseWeapon::CheckEnemyInRange(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos)
{
	for (auto it : m_vectorEnemy)
	{
		int x_dis = abs(characterPos.x - it->Get2DPosition().x);
		int y_dis = abs(characterPos.y - it->Get2DPosition().y);
		float distance = sqrt(x_dis * x_dis + y_dis * y_dis);
		if (distance <= m_range) return true;
	}
	return false;
}

std::shared_ptr<Bullet> BaseWeapon::Fire(Vector2 other, float deltaTime)
{
	m_timeSinceLastFire += deltaTime;
	if (m_timeSinceLastFire >= (0.300f))
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/items/acid.png");
		BulletOfWeapon = std::make_shared<Bullet>(texture, 1, 1, 1, 1.00f);
		BulletOfWeapon->Set2DPosition(m_position.x, m_position.y);
		BulletOfWeapon->SetSize(50, 50);
		BulletOfWeapon->SetTarget(other);
		m_timeSinceLastFire = 0;
		return BulletOfWeapon;
	}
	else
	{
		return 0;
	}
}


