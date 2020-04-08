#include "Powerup.h"
#include "TextureManager.h"
#include "Game.h"

Powerup::Powerup()
{
	TheTextureManager::Instance()->load("../Assets/textures/Powerup.png",
		"powerup", TheGame::Instance()->getRenderer());

	TheTextureManager::Instance()->load("../Assets/textures/cube.png",
		"cube", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("powerup");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::POWERUP);
	setVelocity(glm::vec2(-3.5f, 0.0f));

}

Powerup::~Powerup()
{
}

void Powerup::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	//TheTextureManager::Instance()->draw("powerup", xComponent, yComponent,
		//TheGame::Instance()->getRenderer(), 0, 255, false);

	TheTextureManager::Instance()->draw("cube", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Powerup::update()
{
	m_move();
}

void Powerup::clean()
{
}

void Powerup::m_move()
{
	auto frame = TheGame::Instance()->getFrames();

	setPosition(glm::vec2(getPosition().x + getVelocity().x, 300 + 250 * sin(frame * 0.04)));

}

