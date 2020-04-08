#pragma once
#ifndef __FINISH_LEVEL__
#define __FINISH_LEVEL__
#include "GameObject.h"

class FinishLevel : public GameObject
{
public:
	FinishLevel();
	~FinishLevel();

	void draw() override;
	void update() override;
	void clean() override;
private:
	void m_move();

};

#endif /* define (__FINISH_LEVEL__) */