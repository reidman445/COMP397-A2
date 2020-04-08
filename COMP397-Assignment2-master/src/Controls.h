#pragma once
#ifndef __CONTROLS__
#define __CONTROLS__
#include "DisplayObject.h"

class Controls : public DisplayObject
{
public:
	Controls();
	~Controls();

	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* define (__CONTROLS__) */