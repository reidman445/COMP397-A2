#include "Player.h"
#include "Game.h"
#include "TextureManager.h"

Player::Player(): m_currentFrame(0), m_currentAnimationState(PLAYER_RIGHT), m_speed(5), m_brakeSpeed(0.2f), m_shootRate(0.5f)
{
	TheTextureManager::Instance()->load("../Assets/textures/Enterprise.png",
		"ship", TheGame::Instance()->getRenderer());

	auto size = TheTextureManager::Instance()->getTextureSize("ship");
	
	
	
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet", TheGame::Instance()->getRenderer());


	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0.0f, 255, true);


	switch(m_currentAnimationState)
	{
	case PLAYER_RIGHT:
		//TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["player"],
		//	getPosition().x, getPosition().y, m_currentFrame, 2.0f,
		//	TheGame::Instance()->getRenderer(), 0, alphaValue, true);

		TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0.0f, 255, true);
		break;
	case PLAYER_LEFT:
		//TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["player"],
		//	getPosition().x, getPosition().y, m_currentFrame, 2.0f,
		//	TheGame::Instance()->getRenderer(), 0, alphaValue, true, SDL_FLIP_HORIZONTAL);

		TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0.0f, 255, true);
		break;
	}
	
	
	
}

void Player::update()
{
	setPosition(getPosition()+getVelocity());

	if (m_shootTime > 0)
	{
		m_shootTime -= 0.016f;
	}
	
	m_checkBounds();
	brake(xBrakeDirection,yBrakeDirection);
	
	if (invincible)
	{
		if ( hitFrame + 100 < TheGame::Instance()->getFrames() )
		{
			
			invincible = false;

		}
		alphaValue = 255 * (sin(TheGame::Instance()->getFrames() * 0.5 ) + 1) * 0.5f;
		

	}
	else
	{
		alphaValue = 255;
	}

	
}

void Player::clean()
{
}

void Player::move(Move newMove)
{
	auto currentVelocity = getVelocity();


	switch (newMove)
	{
	case UP:
		if(getVelocity().y > -m_speed)
		{
			setVelocity(glm::vec2(getVelocity().x, -1.0f * m_speed));
		}
		break;
	case DOWN:
		if (getVelocity().y < m_speed)
		{
			setVelocity(glm::vec2(getVelocity().x, 1.0f * m_speed));
		}
		break;
	case LEFT:
		if (getVelocity().x > -m_speed)
		{
			setVelocity(glm::vec2(-1.0f * m_speed, getVelocity().y));
		}
		break;
	case RIGHT:
		if (getVelocity().x < m_speed)
		{
			setVelocity(glm::vec2(1.0f * m_speed, getVelocity().y));
		}
		break;
	}
}

void Player::brake(Move xDirection, Move yDirection)
{
	auto currentVelocity = getVelocity();

	switch (yDirection)
	{
	case UP:
		if (getVelocity().y < 0)
		{
			setVelocity(glm::vec2(getVelocity().x, getVelocity().y + m_brakeSpeed));
		}
		else
		{
			setVelocity(glm::vec2(getVelocity().x, 0));
			yBrakeDirection = EMPTY;
		}
		break;
	case DOWN:
		if (getVelocity().y > 0)
		{
			setVelocity(glm::vec2(getVelocity().x, getVelocity().y - m_brakeSpeed));

		}
		else
		{
			setVelocity(glm::vec2(getVelocity().x, 0));
			yBrakeDirection = EMPTY;

		}
		break;
	}

	
	switch (xDirection)
	{

	case LEFT:
		if (getVelocity().x < 0)
		{
			setVelocity(glm::vec2(getVelocity().x + m_brakeSpeed, getVelocity().y));
		}
		else
		{
			setVelocity(glm::vec2(0, getVelocity().y));
			xBrakeDirection = EMPTY;

		}
		break;
	case RIGHT:
		if (getVelocity().x > 0)
		{
			setVelocity(glm::vec2(getVelocity().x - m_brakeSpeed, getVelocity().y));
		}
		else
		{
			setVelocity(glm::vec2(0, getVelocity().y));
			xBrakeDirection = EMPTY;

		}
		break;
	}
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

float Player::getShootTime()
{
	return m_shootTime;
}

float Player::getShootRate()
{
	return m_shootRate;
}

void Player::setShootTime(float shootTime)
{
	m_shootTime = shootTime;
}

void Player::setShootRate(float shootRate)
{
	m_shootRate = shootRate;
}

float Player::getSpeed()
{
	return m_speed;
}

void Player::setSpeed(float speed)
{
	m_speed = speed;
}


void Player::m_buildAnimations()
{
	Animation playerAnimation = Animation();

	playerAnimation.name = "player";
	for (int i = 1; i < 10; ++i)
	{
		

	}

	//m_pAnimations["player"] = playerAnimation;


}

void Player::m_checkBounds()
{
	//check right bounds
	if (getPosition().x >= (Config::SCREEN_WIDTH * 0.7f)- getWidth() * 0.5f)
	{
		setPosition(glm::vec2((Config::SCREEN_WIDTH * 0.7f) - getWidth() * 0.5f, getPosition().y));
	}

	// check left bounds
	if (getPosition().x <= getWidth() * 0.5f)
	{
		setPosition(glm::vec2(getWidth() * 0.5f, getPosition().y));
	}

	// check bottom bounds
	if (getPosition().y >= Config::SCREEN_HEIGHT - getHeight() * 0.5f)
	{
		setPosition(glm::vec2(getPosition().x, Config::SCREEN_HEIGHT - getHeight() * 0.5f));
	}

	// check top bounds
	if (getPosition().y <= getHeight() * 0.5f)
	{
		setPosition(glm::vec2( getPosition().x, getHeight() * 0.5f));
	}
}
