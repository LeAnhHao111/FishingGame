#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "KeyState.h"
#include "Define.h"
#include <iostream>


SpriteAnimation::SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime) : BaseObject(texture)
{
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
}
SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::Init()
{

}

void SpriteAnimation::Draw(SDL_Renderer* renderer)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->RenderFrame(m_position.x, m_position.y, m_iWidth, m_iHeight, m_spriteRow, m_currentFrame, m_frameCount, m_numAction, m_angle, m_flip);
	}
}

void SpriteAnimation::Update(float deltatime)
{
	m_currentTicks += deltatime;
	if (m_currentTicks >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_frameCount)
		{
			m_currentFrame = 0;
		}
		m_currentTicks -= m_frameTime;
	}
}

void SpriteAnimation::Set2DPosition(float x, float y)
{
	m_position = Vector3((float)x, (float)y, 0.0f);
}


void SpriteAnimation::SetRotation(double angle)
{
	m_angle = angle;
}

void SpriteAnimation::SetFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}

Vector2 SpriteAnimation::Get2DPosition()
{
	return Vector2(m_position.x, m_position.y);
}

void SpriteAnimation::SetSize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_scale = Vector3((float)m_iWidth, (float)m_iHeight, 0.0f);
}

int SpriteAnimation::GetWidth()
{
	return m_iWidth;
}

int SpriteAnimation::GetHeight()
{
	return m_iHeight;
}

char SpriteAnimation::GetFlip()
{
	return m_flip;
}

void SpriteAnimation::MoveLeft(float deltaTime)
{
	if (m_position.x > 0) {
		m_position.x -= 200 * deltaTime;
	}
	else
	{
		m_position.x -= 0 * deltaTime;
	}
}


void SpriteAnimation::MoveRight(float deltaTime)
{
	if (SCREEN_WIDTH - 100 > m_position.x) {
		m_position.x += 200 * deltaTime;
	}
	else
	{
		m_position.x += 0 * deltaTime;
	}
}


void SpriteAnimation::MoveDown(float deltaTime)
{

	m_position.y += 300 * deltaTime;
}
void SpriteAnimation::MoveUp(float deltaTime)
{
	m_position.y -= 500 * deltaTime;
}

void SpriteAnimation::MoveUp(float deltaTime, float speed)
{
	m_position.y -= speed * deltaTime;
}



