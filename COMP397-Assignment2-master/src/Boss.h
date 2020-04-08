#pragma once
#ifndef __BOSS__
#define __BOSS__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>


#include "EnemyMovementType.h"
#include "Move.h"

class Boss : public DisplayObject
{
public:
	Boss();
	~Boss();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void move(EnemyMovementType movement);



	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);

	float getShootTime();
	float getShootRate();
	void setShootTime(float shootTime);
	void setShootRate(float shootRate);
	void setSpeed(float speed);

	void setMovementType(EnemyMovementType movementType);
	glm::vec2 startPosition;
	bool destroyed;

	void setHealth(int health);
	int getHealth();
	
private:

	glm::vec2 offset;
	float m_shootRate;
	float m_shootTime;
	bool m_bMovingBack = false;
	int m_health; 
	
	void m_buildAnimations();

	float m_speed;
	EnemyMovementType m_movementType = FOWARD;

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__BOSS__) */