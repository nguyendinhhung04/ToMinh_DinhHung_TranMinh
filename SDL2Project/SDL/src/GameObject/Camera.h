#pragma once
#include "CMath.h"
#include "SDL.h"
#include "SpriteAnimation.h"
#include "Define.h"
#include "GameManager/Singleton.h"
class Camera : public CSingleton<Camera>
{
public:
	Camera() { m_ViewBox = { 500, 500, SCREEN_WIDTH, SCREEN_HEIDHT }; }
	SDL_Rect GetViewBox();
	Vector2 GetPosition();
	void SetTarget(std::shared_ptr<SpriteAnimation> target);
	void Update(float deltaTime);
	void Init();
private:
	std::shared_ptr<SpriteAnimation> m_Target;
	Vector2 m_Position;
	SDL_Rect m_ViewBox;
	float m_Smooth = 5.0f;
};