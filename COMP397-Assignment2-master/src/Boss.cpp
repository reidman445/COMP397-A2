#include "Boss.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Boss::Boss() : m_currentFrame(0), m_currentAnimationState(PLAYER_RIGHT), m_speed(4), m_shootRate(0.15f), m_health(30)
{

	TheTextureManager::Instance()->load("../Assets/textures/KlingonLarge.png",
		"boss", TheGame::Instance()->getRenderer());

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(200);

	// set frame height
	setHeight(160);

	setPosition(glm::vec2(800.0f, 0));
	setVelocity(glm::vec2(-5.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(BOSS);
	offset = glm::vec2(Util::RandomRange(0, 2), Util::RandomRange(0, 30));
	m_buildAnimations();
}

Boss::~Boss()
= default;

void Boss::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	if (!destroyed)
	{
		//TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["boss"],
		//	getPosition().x, getPosition().y, m_currentFrame, 2.0f,
		//	TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);

		TheTextureManager::Instance()->draw("boss", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0.0f, 255, true);
		
	}



}

void Boss::update()
{

	if (getPosition().x > 700 && m_movementType != BACKWARDS)
	{
		move(FOWARD);
	}
	else
	{

		move(BACK_AND_FORTH);

	}


	if (m_shootTime > 0)
	{
		m_shootTime -= 0.016f;
	}

}

void Boss::clean()
{
}

void Boss::move(EnemyMovementType movement)
{

	auto frame = TheGame::Instance()->getFrames();
	
	if (getPosition().x > 800)
	{
		std::cout << "aqui" << std::endl;
		setVelocity(glm::vec2(-5, 0));
		m_bMovingBack = false;

	} else if (getPosition().x <= 50)
	{
		std::cout << "aqui2" << std::endl;
		setVelocity(glm::vec2(5, 0));
		m_bMovingBack = true;
	} else if (!m_bMovingBack)
	{
		std::cout << "aqui3" << std::endl;
		setVelocity(glm::vec2(-10, 0));

	} else
	{
		setVelocity(glm::vec2(5, 0));

	}
	setPosition(glm::vec2(getPosition().x + getVelocity().x, 350 + 100 * sin(frame * 0.05)));

}

void Boss::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Boss::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;
}

float Boss::getShootTime()
{
	return m_shootTime;
}

float Boss::getShootRate()
{
	return m_shootRate;
}

void Boss::setShootTime(float shootTime)
{
	m_shootTime = shootTime;
}

void Boss::setShootRate(float shootRate)
{
	m_shootRate = shootRate;
}

void Boss::setSpeed(float speed)
{
	m_speed = speed;
}

void Boss::setMovementType(EnemyMovementType movementType)
{
	m_movementType = movementType;
}

void Boss::setHealth(int health)
{
	m_health = health;
}

int Boss::getHealth()
{
	return m_health;
}

void Boss::m_buildAnimations()
{
	Animation enemyAnimation = Animation();

	enemyAnimation.name = "boss";

	enemyAnimation.frames.push_back(m_pSpriteSheet->getFrame("Boss"));


	m_pAnimations["boss"] = enemyAnimation;


}
