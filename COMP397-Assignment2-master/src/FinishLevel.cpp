#include "FinishLevel.h"
#include "Game.h"

FinishLevel::FinishLevel()
{

	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::FINISH_LEVEL);
	setVelocity(glm::vec2(0.0f, 0.0f));

}

FinishLevel::~FinishLevel()
{
}



void FinishLevel::draw()
{
}

void FinishLevel::update()
{
	m_move();
}

void FinishLevel::clean()
{
}

void FinishLevel::m_move()
{

	setPosition(glm::vec2(getPosition() + getVelocity()));

}

