#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "ImputManager.h"
#include "Scoreboard.h"

class StartScreen : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;

	Texture* mFondo[2];

public:

	StartScreen();
	~StartScreen();

	void Update();

	void Render();

};

#endif
