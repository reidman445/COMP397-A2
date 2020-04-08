#pragma once
#ifndef __POWERUP__
#define __POWERUP__
#include "DisplayObject.h"
#include <sstream>

class Powerup : public DisplayObject
{
public:
	Powerup();
	~Powerup();

	void draw() override;
	void update() override;
	void clean() override;
private:
	void m_move();

};

#endif /* define (__ROCK__) */