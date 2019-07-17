// Created by kevin20012 on 01/04/2019.
#ifndef _BLENSTER_H
#define _BLENSTER_H
#include "Enemy.h"
#include "CircleCollider.h"
#include "AudioManager.h"

class Blenster : public Enemy {

public:

	Blenster(bool especial);
	~Blenster();

	void Hit(PhysEntity* other) override;

    void Update() override;
};

#endif

