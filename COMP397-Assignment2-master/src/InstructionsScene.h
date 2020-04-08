#pragma once
#ifndef __INSTRUCTIONS_SCENE__
#define __INSTRUCTIONS_SCENE__

#include "Background.h"
#include "BackToMenuButton.h"
#include "Controls.h"
#include "InstructionsButton.h"
#include "Scene.h"
#include "Label.h"
#include "QuitButton.h"
#include "StartButton.h"

class InstructionsScene final : public Scene
{
public:
	InstructionsScene();
	~InstructionsScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	glm::vec2 getMousePosition() const;

private:
	glm::vec2 m_mousePosition;

	Label* m_pStartLabel{};
	Controls* m_pControls;
	Label* m_pMoveLabel{};
	Label* m_pShootLabel{};

	Background* m_pBackground;

	
	BackToMenuButton* m_pBackToMenuButton;

};

#endif /* defined (__INSTRUCTIONS_SCENE__) */