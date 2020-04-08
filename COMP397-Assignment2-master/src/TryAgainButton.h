#pragma once
#ifndef __TRY_AGAIN_BUTTON__
#define __TRY_AGAIN_BUTTON__

#include "Button.h"

class TryAgainButton : public Button
{
public:
	TryAgainButton();
	~TryAgainButton();


	bool ButtonClick() override;
private:
	bool m_isClicked;
};

#endif /* defined (__TRY_AGAIN_BUTTON__) */