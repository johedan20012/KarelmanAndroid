//
// Created by kevin20012 on 26/05/2019.
//
#include "Spawner.h"


Spawner::Spawner(TYPE type) {
    mType = type;

    mTimer = Timer::Instance();

    mSpawnDelay = rand() % 100;
    mSpawnDelay /= 100;
    mSpawnDelay += 1.0f;

    mPosChangeDelay = rand() % 25;
    mPosChangeDelay += 10;
    mPosChangeTimer = mPosChangeDelay;

    mTexture = new Texture("ScreenGamepad/button1.png",100,100);
    mTexture->Pos(VEC2_ZERO);
    mTexture->Parent(this);

    mSpawnTimer = 0;
}

Spawner::~Spawner() {
    delete mTexture;
    mTexture = NULL;
}

void Spawner::Update(std::vector <Enemy*>* enemigos,int stage) {
    if(mSpawnTimer > 0){
        mSpawnTimer -= mTimer->DeltaTime();
        if(mSpawnTimer < 0) mSpawnTimer = 0;
    }
    if(mPosChangeTimer > 0){
        mPosChangeTimer -= mTimer->DeltaTime();
        if(mPosChangeTimer < 0) mPosChangeTimer = 0;
    }
    if(mPosChangeTimer == 0){
        Vector2 pos;
        pos.x = rand() % (Graphics::Instance()->SCREEN_WIDTH-50);
        pos.x += 50;
        pos.y = rand() % (Graphics::Instance()->SCREEN_HEIGHT-50);
        pos.y += 50;
        Pos(pos);
        mSpawnTimer = mSpawnDelay/stage;
        mPosChangeDelay = rand() % 25;
        mPosChangeDelay += 10;
        mPosChangeTimer = mPosChangeDelay;

        int aux = rand() % 3;
        mType = (TYPE) aux;
    }
    if(mSpawnTimer == 0){ ///Espawnear un mounstro
        Enemy* en = NULL;
        int posibilidad = (100/(stage*2) < 5)? 5 : (100/stage);
        bool especial = (rand()%posibilidad == 1);
        switch(mType){
            case blenster:
                en = new Blenster(especial);
                break;
            case clumster:
                en = new Clumster(especial);
                break;
            case monster:
                en = new Monster(especial);
                break;
        }
        if(en == NULL) return;
        en->Pos(Pos());
        enemigos->push_back(en);
        mSpawnTimer = mSpawnDelay/stage;
    }
}

void Spawner::Render() {
    mTexture->Render();
}
