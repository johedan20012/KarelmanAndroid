#include "GameEntity.h"

GameEntity::GameEntity(Vector2 pos) {

	mPos = pos;

	mRotation = 0.0f;

	mActive = true;

	mParent = NULL;

	mScale = VEC2_ONE;
}

GameEntity::~GameEntity(){

	mParent = NULL;
}

void GameEntity::Pos(Vector2 pos){

	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space) {

	if (space == local || mParent == NULL) {

		return mPos;
	}

	GameEntity* parent = mParent;
	Vector2 finalPos = mPos, parentScale = VEC2_ZERO;

	do {
		
		parentScale = mParent->Scale(local);

		Vector2 aux = Vector2(finalPos.x * parentScale.x, finalPos.y * parentScale.y);
		finalPos = RotateVector(aux, parent->Rotation(local));
		finalPos += parent->Pos(local);

		parent = parent->Parent();

	} while (parent);

	
	return finalPos;
}

void GameEntity::Rotation(float r) {

	mRotation = r;

	if (mRotation > 360.0f) {
		mRotation -= 360.0f;
	}
	if (mRotation < 0.0f) {
		mRotation += 360.0f;
	}
}

float GameEntity::Rotation(SPACE space) {

	if (space == local || mParent == NULL) {
		
		return mRotation;
	}

	return mParent->Rotation(world) + mRotation;
}

void GameEntity::Scale(Vector2 scale) {

	mScale = scale;
}

Vector2 GameEntity::Scale(SPACE space) {

	if (space == local || mParent == NULL) {
		return mScale;
	}

	Vector2 scale = mParent->Scale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;


	return scale;
}

void GameEntity::Active(bool active) {

	mActive = active;
}

bool GameEntity::Active() {

	return mActive;
}

void GameEntity::Parent(GameEntity* parent) {

	if (parent == NULL) {
		
		mPos = Pos(world);
		mRotation = Rotation(world);
		mScale = Scale(world);

	} else {

		if (mParent != NULL) {
			Parent(NULL);
		}

		Vector2 parentScale = parent->Scale(world);
		Vector2 aux = Pos(world) - parent->Pos(world);
		mPos = RotateVector( aux , -parent->Rotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		mRotation -= parent->Rotation(world);

		mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameEntity* GameEntity::Parent() {

	return mParent;
}

void GameEntity::Translate(Vector2 vec,SPACE space) {

	if (space == world) {
		mPos += vec;
	} else {

		mPos += RotateVector(vec, Rotation());
	}
}

void GameEntity::Rotate(float amount) {

	Rotation(mRotation + amount);
}

void GameEntity::Update() {


}

void GameEntity::Render() {


}