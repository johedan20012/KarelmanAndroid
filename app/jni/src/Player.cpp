#include "Player.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

Player::Player() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mShip = new Texture("karelman11.png",100,100);
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 500.0f;
	mMoveBounds = Vector2(50, 50);

	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i] = new Bullet(true);
	}
	AddCollider(new BoxCollider(Vector2(37.0f, 75.0f)),Vector2(0.0f, 12.0f));
	AddCollider(new BoxCollider(Vector2(60.0f, 20.0f)));
	AddCollider(new BoxCollider(Vector2(17.0f, 12.0f)), Vector2(-3.0f, -30.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

    mFireTimer = 0;
}

void Player::HandleFiring() {
	if(mFireTimer > 0){
		mFireTimer -= mTimer->DeltaTime();
		if(mFireTimer < 0){
			mFireTimer = 0;
		}
	}
	//SDL_Log("mFire Timer %9.3f",mFireTimer);
	Vector2 joystickValue = mInput->GetJoystickState(1);
	if (joystickValue.x != 0 || joystickValue.y != 0) {
		if (mFireTimer > 0) {
			return;
		}
		for (int i = 0; i < MAX_BULLETS; i++) {

			if (!mBullets[i]->Active()) {
				mFireTimer = mFireDelay;
				mBullets[i]->Fire(Pos(), Rotation(world));
				mAudio->PlaySFX("fire.wav");
				break;
			}
		}
	}
}

Player::~Player() {

	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mShip;
	mShip = NULL;

	for (int i = 0; i < MAX_BULLETS; i++) {

		delete mBullets[i];
		mBullets[i] = NULL;
	}
}

void Player::HandleMovement() {

    Vector2 joystickValue = mInput->GetJoystickState(0);
    if(joystickValue.x != 0 || joystickValue.y !=0) {
		Translate(intearVector(joystickValue * -1 * mMoveSpeed * mTimer->DeltaTime()), world);
	}
	joystickValue = mInput->GetJoystickState(1);
	if (joystickValue.x != 0 || joystickValue.y != 0) {
		Rotation(GetAngleFromYAxisToVector(joystickValue));
	}
	Vector2 pos = Pos(local);
	if (pos.x > Graphics::Instance()->SCREEN_WIDTH - mMoveBounds.x) {

		pos.x = Graphics::Instance()->SCREEN_WIDTH - mMoveBounds.x;
	} else if (pos.x < mMoveBounds.y) {

		pos.x = mMoveBounds.y;
	}

    if (pos.y > Graphics::Instance()->SCREEN_HEIGHT - mMoveBounds.x) {

        pos.y = Graphics::Instance()->SCREEN_HEIGHT - mMoveBounds.x;
    } else if (pos.y < mMoveBounds.y) {

        pos.y = mMoveBounds.y;
    }

	Pos(pos);
}

void Player::Hit(PhysEntity* other) {
	mAudio->PlaySFX("playerdestroyer.wav");
	mWasHit = true;
}

bool Player::WasHit() {

	return mWasHit;
}

int Player::Score() {

	return mScore;
}

int Player::Lives() {

	return mLives;
}

void Player::AddScore(int change) {

	mScore += change;
}

void Player::Update() {
	if (Active()) {

		HandleMovement();
		HandleFiring();
	}

	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Update();
	}
}

void Player::Render() {

    mShip->Render();

	for (int i = 0; i < MAX_BULLETS; i++) {

		mBullets[i]->Render();
	}

	PhysEntity::Render();

 }