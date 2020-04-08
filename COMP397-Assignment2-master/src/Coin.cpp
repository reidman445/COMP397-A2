#include "Coin.h"
#include "Game.h"
#include "TextureManager.h"

Coin::Coin() : m_currentFrame(0), m_currentAnimationState(PLAYER_RIGHT)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(20);

	// set frame height
	setHeight(20);

	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(-3.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(COIN);

	m_buildAnimations();
}

Coin::~Coin()
= default;

void Coin::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;


		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["coin"],
			getPosition().x, getPosition().y, m_currentFrame, 0.4f,
			TheGame::Instance()->getRenderer(), 0, 255, true);

}

void Coin::update()
{
	setPosition(getPosition() + getVelocity());

}

void Coin::clean()
{
}


void Coin::m_buildAnimations()
{
	Animation CoinAnimation = Animation();

	CoinAnimation.name = "coin";
	for (int i = 1; i < 7; ++i)
	{
		CoinAnimation.frames.push_back(m_pSpriteSheet->getFrame("Coin" + std::to_string(i)));

	}

	m_pAnimations["coin"] = CoinAnimation;


}
