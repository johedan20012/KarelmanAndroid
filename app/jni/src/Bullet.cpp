#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Bullet::Bullet(bool friendly) {

	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mTexture = new Texture("bala1.png",30,50);
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);


	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	if (friendly) {

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectiles);
	} else {

		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectiles);
	}
}

Bullet::~Bullet() {

	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Bullet::Fire(Vector2 pos,float angle) {

	Pos(pos);
	Rotation(angle);
	Active(true);
}

void Bullet::Reload() {

	Active(false);
}

void Bullet::Hit(PhysEntity* other) {

	Reload();
}

bool Bullet::IgnoreCollisions() {

	return !Active();
}

void Bullet::Update() {
	
	if (Active()) {

		Translate(-VEC2_UP * mSpeed * mTimer->DeltaTime(),local);

		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER || pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER) {

			Reload();
		}
	}
}

void Bullet :: Render() {

	if (Active()) {

		mTexture->Render();
		PhysEntity::Render();
	}
}


