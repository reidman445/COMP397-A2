#pragma once
#ifndef __ROCK__
#define __ROCK__
#include "DisplayObject.h"
#include <sstream>

class Rock : public DisplayObject
{
public:
	Rock();
	~Rock();

	void draw() override;
	void update() override;
	void clean() override;
private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};

#endif /* define (__ROCK__) */