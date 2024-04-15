#include "Weapon.h"
#include "Weapon.h"
#include "TextureManager.h"
#include <cmath>
#define RANGE 100
Weapon::Weapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
	m_range = RANGE;
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
	//m_bulletOfWeapon = NULL;
	m_lastUpdate = SDL_GetTicks();
	m_fireSpeed = 1; currentTime = 0;
	Init();
}
Weapon::~Weapon()
{

}

void Weapon::Init()
{

}

void Weapon::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void Weapon::Update(float deltatime)
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

void Weapon::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}

void Weapon::SetRotation(double angle)
{
	m_angle = angle;
}

void Weapon::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 Weapon::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void Weapon::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int Weapon::GetWidth()
{
	return m_iWidth;
}

int Weapon::GetHeight()
{
	return m_iHeight;
}


void Weapon::Flip(bool targetDir)
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

//update 
void Weapon::UpdateBullets(float deltaTime)
{
	if (!m_bullets.empty()) {
		m_bullets[m_bullets.size() - 1]->Update(deltaTime);
	}
}

//Fire
void Weapon::Fire(Vector2 other)
{
	if (!m_bullets.empty()) {
		m_bullets[m_bullets.size() - 1]->MoveToTarget(other);
	}

}


void Weapon::FireP2( SDL_Renderer* renderer)
{
	if (!m_bullets.empty()) {
		m_bullets[m_bullets.size() - 1]->Draw(renderer);
	}
}
//range
bool Weapon::IsEnemyInRange(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos)
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

void Weapon :: initBullet(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos, float deltaTime)
{
	currentTime += deltaTime;

	if (currentTime >= 1.f) { // Check if 1 second has passed since the last bullet
		if (IsEnemyInRange(m_vectorEnemy, characterPos)) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("brotato_presskit/items/acid.png");
			auto bullet = std::make_shared<Bullet>(texture, 1, 1, 1, 1.00f);
			bullet->Set2DPosition(m_position.x, m_position.y);
			bullet->SetSize(30, 30);
			m_bullets.push_back(bullet);
		}
		currentTime = 0.0f; // Reset the timer
	}
}


void Weapon::followPlayer(std::shared_ptr<SpriteAnimation> player)
{
	Set2DPosition(player->Get2DPosition().x,player->Get2DPosition().y);
}




