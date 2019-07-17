#include "Enemy.h"
#include "PhysicsManager.h"

Player* Enemy::sPlayer = nullptr;


void Enemy::CurrentPlayer(Player * player){

	sPlayer = player;
}

Enemy::Enemy() {

	mTimer = Timer::Instance();

	mTextures[0] = NULL;
	mTextures[1] = NULL;

	mSpeed = 400.0f;

	float grados = rand() % 360;
    mDirection = VEC2_UP;
    mDirection = RotateVector(mDirection,grados);

	mDead = false;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);
}

Enemy::~Enemy() {

	mTimer = NULL;

    PhysicsManager::Instance()->UnregisterEntity(mId);

	delete mTextures[0];
	mTextures[0] = NULL;

	if(mTextures[1] != NULL) delete mTextures[1];
	mTextures[1] = NULL;

}

void Enemy::Hit(PhysEntity * other){

	mDead = true;
	Parent(nullptr);
}

bool Enemy::IgnoreCollisions() {

	return mDead;
}

bool Enemy::WasHit() {

    return mDead;
}

Enemy::TYPES Enemy::Type() {

	return mType;
}

void Enemy::Update() {

}

void Enemy::Render() {

	if(!mDead){
		mTextures[0]->Render();
		if(mSpecial) mTextures[1]->Render();
	}

    PhysEntity::Render();
}

bool Enemy::IsEspecial() {
	return mSpecial;
}
