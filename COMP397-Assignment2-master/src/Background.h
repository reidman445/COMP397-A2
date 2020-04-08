#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__
#include "DisplayObject.h"
#include <sstream>

class Background : public DisplayObject
{
public:
	Background();
	~Background();

	void draw() override;
	void update() override;
	void clean() override;
private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};

#endif /* define (__BACKGROUND__) */