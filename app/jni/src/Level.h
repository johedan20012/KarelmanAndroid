#ifndef _LEVEL_H
#define _LEVEL_H
#include "ImputManager.h"
#include "Player.h"
#include "Spawner.h"
#include "Scoreboard.h"

class Level : public GameEntity {

public:

	enum LEVEL_STATES { running,terminated, gameover };

private:

	Timer* mTimer;

	Player* mPlayer;
	bool mPlayerHit;

    Texture* mFondo;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	bool mATopeActivado = false;
	float mATopeTimer = 0.0f;
	float mATopeDelay;

	AnimatedTexture* mATopeText;

    Scoreboard* mScore;

    Scoreboard* mMonsters;

    Scoreboard* mStage;

	LEVEL_STATES mCurrentState;

	std::vector<Enemy*> mEnemies;

	static const int MAX_SPAWNS = 4;

	Spawner* mSpawns[MAX_SPAWNS];

	bool aux;

	float mCurrentStage = 1; //"Nivel" del juego , entre mas tiempo pase este numero sera más grande

private:
	void HandleCollisions();
	void HandlePlayerDeath();

	void HandleEnemySpawning();

public:

	Level(Player* player);
	~Level();

	LEVEL_STATES State();

	void Update();

	void Render();
};

#endif 

