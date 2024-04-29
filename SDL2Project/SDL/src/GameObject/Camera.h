#pragma once
#include "CMath.h"
#include "SDL.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"
#include "Define.h"
#include "GameManager/Singleton.h"
#define WIDTH_OFFSET 300
#define HEIGHT_OFFSET 100
class Camera : public CSingleton<Camera>
{
public:
	Camera() { m_ViewBox = { 500, 500, SCREEN_WIDTH, SCREEN_HEIDHT }; }
	SDL_Rect GetViewBox();
	Vector2 GetPosition();

	void SetViewBox(float x, float y);
	void SetTarget(std::shared_ptr<SpriteAnimation> target, std::shared_ptr<Sprite2D> map);
	void Update(float deltaTime);
	void Init();
private:
	std::shared_ptr<SpriteAnimation> m_Target;
	std::shared_ptr<Sprite2D> m_map;
	Vector2 m_Position;
	SDL_Rect m_ViewBox;
	float m_Smooth = 5.0f;
};