#pragma once
#ifndef __COIN__
#define __COIN__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

#include "Move.h"

class Coin : public DisplayObject
{
public:
	Coin();
	~Coin();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__COIN__) */