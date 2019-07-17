//
// Created by kevin20012 on 26/05/2019.
//
#ifndef _SPAWNER_H
#define _SPAWNER_H

#include "Texture.h"
#include "GameEntity.h"
#include "Timer.h"
#include "Blenster.h"
#include "Clumster.h"
#include "Monster.h"

class Spawner : public GameEntity{
    public:

    enum TYPE { blenster = 0,clumster,monster };

    private:

        Timer* mTimer;

        Texture* mTexture; //Nota , para el futuro agregar animación al momento de spawnear

        float mSpawnDelay = 0.5f;
        float mSpawnTimer;

        float mPosChangeDelay;
        float mPosChangeTimer;

        TYPE mType;
    public:
        Spawner(TYPE type);
        ~Spawner();

        void Update(std::vector <Enemy*>* enemigos,int stage);
        void Render();
};

#endif
