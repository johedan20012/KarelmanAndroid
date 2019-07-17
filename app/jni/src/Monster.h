// Created by kevin20012 on 01/04/2019.
#ifndef _MONSTER_H
#define _MONSTER_H

#include "Enemy.h"
#include "CircleCollider.h"
#include "AudioManager.h"
#include "MathHelper.h"

class Monster : public Enemy {

private:

    float mCurrentTime;
    float mDelayChange;

public:

    Monster(bool especial);
    ~Monster();

    void Hit(PhysEntity* other) override;

    void Update() override;
};

#endif
