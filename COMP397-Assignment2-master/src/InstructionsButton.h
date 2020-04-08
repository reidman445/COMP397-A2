#pragma once
#ifndef __INSTRUCTIONS_BUTTON__
#define __INSTRUCTIONS_BUTTON__

#include "Button.h"

class InstructionsButton : public Button
{
public:
	InstructionsButton();
	~InstructionsButton();


	bool ButtonClick() override;
private:
	bool m_isClicked;
};

#endif /* defined (__INSTRUCTIONS_BUTTON__) */