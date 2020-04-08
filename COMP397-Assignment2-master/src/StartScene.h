#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Background.h"
#include "InstructionsButton.h"
#include "Scene.h"
#include "Label.h"
#include "QuitButton.h"
#include "StartButton.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

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
	StartButton* m_pStartButton;
	InstructionsButton* m_pInstructionsButton;

	Background* m_pBackground;
	
	QuitButton* m_pQuitButton;

};

#endif /* defined (__START_SCENE__) */