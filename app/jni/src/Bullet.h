#ifndef _BULLET_H
#define _BULLET_H
#include "PhysEntity.h"
#include "Timer.h"

class Bullet : public PhysEntity {

private:

	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	float mSpeed;

	Texture* mTexture;



public:

	Bullet(bool friendly);
	~Bullet();

	void Fire(Vector2 pos,float angle);
	void Reload();

	void Hit(PhysEntity* other) override;

	void Update();

	void Render();

private:

	bool IgnoreCollisions() override;
};

#endif 
