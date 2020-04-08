#include "Bullet.h"
#include "Game.h"
#include <utility>

#include "TextureManager.h"

Bullet::Bullet() : m_currentFrame(0), m_bIsActive(false)
{

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(15);

	// set frame height
	setHeight(4);

	setPosition(glm::vec2(2000, 2000.0f));
	setVelocity(glm::vec2(8.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(BULLET);

	m_buildAnimations();


}

Bullet::~Bullet()
= default;

void Bullet::draw()
{


		TheTextureManager::Instance()->playAnimation(
			"spritesheet", m_pAnimations["bullet"],
			getPosition().x, getPosition().y, m_currentFrame, 0.5f,
			TheGame::Instance()->getRenderer(), 0, 255, true);


}

void Bullet::update()
{
	setPosition(getPosition() + getVelocity());
}

void Bullet::clean()
{
}

void Bullet::activate()
{
	m_currentFrame = 0;
	m_bIsActive = true;
}

void Bullet::deactivate()
{
	setPosition(1000.0f, 1000.0f);
	m_bIsActive = false;
}

bool Bullet::isActive()
{
	return  m_bIsActive;
}

void Bullet::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;

}

void Bullet::m_buildAnimations()
{
	Animation explosionAnimation = Animation();

	explosionAnimation.name = "bullet";

	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("bullet1"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("bullet2"));

	m_pAnimations["bullet"] = explosionAnimation;

}
