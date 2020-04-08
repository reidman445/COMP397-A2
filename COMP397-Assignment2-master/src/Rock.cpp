#include "Rock.h"
#include "TextureManager.h"
#include "Game.h"

Rock::Rock()
{
	TheTextureManager::Instance()->load("../Assets/textures/Rock.jpg",
		"rock", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("rock");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::BACKGROUND);
	setVelocity(glm::vec2(-5.0f, 0.0f));

}

Rock::~Rock()
{
}

void Rock::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("rock", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Rock::update()
{
	m_move();
	m_checkBounds();
}

void Rock::clean()
{
}

void Rock::m_move()
{
	setPosition(getPosition() + getVelocity());
}

void Rock::m_checkBounds()
{
	if (getPosition().x <= 0.0f)
	{
		m_reset();
	}
}

void Rock::m_reset()
{
	setPosition(glm::vec2(1000.0f, 0.0f));
}