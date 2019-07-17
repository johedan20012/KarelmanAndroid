#ifndef _ENEMY_H
#define _ENEMY_H
#include "AnimatedTexture.h"
#include "PhysEntity.h"
#include "Player.h"

class Enemy : public PhysEntity {

public:

	enum TYPES { blenster,clumster,monster };

protected:

	static Player* sPlayer;

	Timer* mTimer;

	Texture* mTextures[2]; //dos texturas , la normal y la amscara de mounstro especial

	bool  mDead;

	bool mSpecial = false;

	float mSpeed;
	Vector2 mDirection;

	TYPES mType;

protected:

	bool IgnoreCollisions() override;

public:

	static void CurrentPlayer(Player* player);

	Enemy();
	virtual ~Enemy();

	virtual void Hit(PhysEntity* other) override;
	bool WasHit();

	bool IsEspecial();

	TYPES Type();

	virtual void Update();

	void Render();
};

#endif 
