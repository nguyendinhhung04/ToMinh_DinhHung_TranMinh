#include "BaseWeapon.h"
#include "TextureManager.h"
#include <cmath>
#define INITIAL_RANGE 300
#define INITIAL_FIRESPEED 1
#define PI 3.14159265
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
	m_angle = 180.00;
	m_flip = SDL_FLIP_NONE;
	damage = 10;
}

BaseWeapon::BaseWeapon(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime,std::string bullet_path,float damage, float fire_speed, float range) : BaseObject(texture)
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
	m_fireSpeed = fire_speed;
	m_range = range;
	//BulletOfWeapon = new BulletOfWeapon();
	m_angle = 180.00;
	m_flip = SDL_FLIP_NONE;
	this->bullet_path = bullet_path;
	this->damage = damage;
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

SDL_RendererFlip BaseWeapon::GetFlip()
{
	return m_flip;
}

void BaseWeapon::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 BaseWeapon::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

double BaseWeapon::GetRotation()
{
	return m_angle;
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



/*
void BaseWeapon::AimToEnemy(Vector2 enemy)
{
	SetRotation(atan2(enemy.x- Get2DPosition().x, enemy.y-Get2DPosition().y) * (180 / PI));
	printf("%f\n", atan2(enemy.x - Get2DPosition().x, enemy.y - Get2DPosition().y) * (180 / PI));

}
*/

void BaseWeapon::AimToEnemy(std::shared_ptr<enemy> enemy)
{
	float a = enemy->Get2DPosition().x + enemy->GetWidth() / 2 - Get2DPosition().x - GetWidth()/2;
	float b = enemy->Get2DPosition().y + enemy->GetHeight() / 2 - Get2DPosition().y - GetHeight() / 2;
	float c = atan2(a, b) * (180 / PI);
	if (c >= 0.10000 && c <= 180)
	{
		SetFlip(SDL_FLIP_NONE);
	}
	else
	{
		SetFlip(SDL_FLIP_VERTICAL);
	}

	SetRotation(-(atan2( a,b ) * (180 / PI) - 90));
	//printf("%f_____", atan2(a, b)* (180 / PI));
	//printf("%f\n", -(atan2(a, b) * (180 / PI) - 90));
}



//range
bool BaseWeapon::CheckEnemyInRange(std::vector<std::shared_ptr<enemy>> m_vectorEnemy, Vector2 characterPos)
{
	for (auto it : m_vectorEnemy)
	{
		float x_dis = abs(characterPos.x - it->Get2DPosition().x);
		float y_dis = abs(characterPos.y - it->Get2DPosition().y);
		float distance = sqrt(x_dis * x_dis + y_dis * y_dis);
		if (distance <= m_range) return true;
	}
	return false;
}

std::shared_ptr<Bullet> BaseWeapon::Fire( float deltaTime, std::vector<std::shared_ptr<enemy>> tempVector)
{
	m_timeSinceLastFire += deltaTime;
	if (m_timeSinceLastFire >= (0.300f))
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture("Bullet/Laser_Sprites/11.png");
		if (bullet_path != "") texture = ResourceManagers::GetInstance()->GetTexture(bullet_path);
		BulletOfWeapon = std::make_shared<Bullet>(texture, 1, 1, 1, 1.00f);
		BulletOfWeapon->Set2DPosition(m_position.x + GetWidth()/2, m_position.y + GetHeight()/2);
		BulletOfWeapon->setDamage(damage);
		BulletOfWeapon->SetSize(178/3, 41/3);

		std::vector<std::shared_ptr<enemy>> m_vectorDistanceEnemy;
		m_vectorDistanceEnemy = tempVector;
		if (m_vectorDistanceEnemy.size() >= 1)
		{
			float minDistance = 1000000;
			auto temp = m_vectorDistanceEnemy.begin();
			for (auto it = m_vectorDistanceEnemy.begin(); it != m_vectorDistanceEnemy.end(); ++it)
			{
				
				float a = ((*it)->Get2DPosition().x + (*it)->GetWidth()/2 ) - (Get2DPosition().x +GetWidth()/2);
				float b = ((*it)->Get2DPosition().y + (*it)->GetHeight()/2) - (Get2DPosition().y + +GetHeight()/2);

				float distance = sqrt(pow(a, 2) + pow(b, 2));
				if (distance < minDistance)
				{
					minDistance = distance;
					temp = it;
				}
			}
			Vector2 Nearest;
			Nearest.x = (*temp)->Get2DPosition().x + (*temp)->GetWidth() / 2;
			Nearest.y = (*temp)->Get2DPosition().y + (*temp)->GetHeight() / 2;
			AimToEnemy((*temp));
			BulletOfWeapon->SetTarget(Nearest);
			BulletOfWeapon->SetRotation(GetRotation());
			BulletOfWeapon->SetFlip(GetFlip());
			m_timeSinceLastFire = 0;
			return BulletOfWeapon;
		}
		else
		{
			return 0;
		}


	}
	else
	{
		return 0;
	}
}


