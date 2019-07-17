// Created by kevin20012 on 01/04/2019.
#ifndef _CLUMSTER_H
#define _CLUMSTER_H
#include "Enemy.h"
#include "CircleCollider.h"
#include "AudioManager.h"

class Clumster : public Enemy {

public:

    Clumster(bool especial);
    ~Clumster();

    void Hit(PhysEntity* other) override;

    void Update() override;
};

#endif
