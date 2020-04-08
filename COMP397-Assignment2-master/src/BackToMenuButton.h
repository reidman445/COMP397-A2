#pragma once
#ifndef __BACK_TO_MENU_BUTTON__
#define __BACK_TO_MENU_BUTTON__

#include "Button.h"

class BackToMenuButton : public Button
{
public:
	BackToMenuButton();
	~BackToMenuButton();


	bool ButtonClick() override;
private:
	bool m_isClicked;
};

#endif /* defined (__BACK_TO_MENU_BUTTON__) */