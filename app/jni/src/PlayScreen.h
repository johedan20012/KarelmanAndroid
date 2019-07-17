#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "Level.h"


class PlayScreen : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;
	//AudioManager* mAudio;

	Level* mLevel;

	Player* mPlayer;

public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	bool GameOver();

	void Update();

	void Render();
};

#endif 

