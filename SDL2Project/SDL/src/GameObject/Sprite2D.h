#pragma once
#include"BaseObject.h"

enum SpriteType
{
	STATIC,
	DYNAMIC
};

class Sprite2D : public BaseObject
{
protected:
	int m_iWidth;
	int m_iHeight;
	SDL_RendererFlip m_flip;
	SpriteType m_type;

public:
	Sprite2D() : BaseObject(), m_iWidth(0), m_iHeight(0), m_type(SpriteType::DYNAMIC) {}
	Sprite2D( std::shared_ptr<TextureManager> texture, SDL_RendererFlip flip);
	void Init() override;
	void Draw(SDL_Renderer * renderer) override;

	void Update(float deltatime) override;
	void Set2DPosition(float x, float y);
	Vector3		Get2DPosition();
	void SetSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetRotation(double angle);
	void SetFlip(SDL_RendererFlip flip);

	SpriteType GetType();
	void SetType(SpriteType type);

	//Moving
	float m_MoveSpeed;
	void MoveLeft(float deltaTime, float speed);
	void MoveRight(float deltaTime, float speed);
	void MoveUp(float deltaTime, float speed);
	void MoveDown(float deltaTime, float speed);
	void MoveLeftDown(float deltaTime, float speed);
	void MoveLeftUp(float deltaTime, float speed);
	void MoveRightUp(float deltaTime, float speed);
	void MoveRightDown(float deltaTime, float speed);



};

