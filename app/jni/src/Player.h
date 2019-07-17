#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "ImputManager.h"
#include "AudioManager.h"
#include "Bullet.h"

class Player : public PhysEntity {

private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mWasHit;

	int mScore;
	int mLives;

	Texture* mShip;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	static const int MAX_BULLETS = 8;
	Bullet* mBullets[MAX_BULLETS];


	const float mFireDelay = 0.2;
	float mFireTimer;

private:

	void HandleMovement();
	void HandleFiring();

public:

	Player();
	~Player();

	void Hit(PhysEntity* other) override;
	bool WasHit();

	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void Update();

	void Render();
};

#endif

