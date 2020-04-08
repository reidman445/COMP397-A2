#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

#include "Move.h"

class Player : public DisplayObject
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void move(Move);
	Move xBrakeDirection;
	Move yBrakeDirection;

	void brake(Move xDirection, Move yDirection);

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);

	float getShootTime();
	float getShootRate();
	void setShootTime(float shootTime);
	void setShootRate(float shootRate);

	float getSpeed();
	void setSpeed(float speed);

	bool invincible = false;
	glm::uint32 hitFrame;

private:

	float m_shootRate;
	float m_shootTime;
	
	void m_buildAnimations();
	void m_checkBounds();
	float m_speed;
	float m_brakeSpeed;

	float alphaValue = 255.0f;

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__PLAYER__) */