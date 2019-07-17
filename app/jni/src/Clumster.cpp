// Created by kevin20012 on 01/04/2019.
#include "Clumster.h"

Clumster::Clumster(bool especial)
    : Enemy()
{
    mTextures[0] = new Texture("clumster2.png",75,75);
    mTextures[0]->Parent(this);
    mTextures[0]->Pos(VEC2_ZERO);

    mSpecial = especial;
    if(mSpecial) {
        mTextures[1] = new Texture("special.png", 75, 75);
        mTextures[1]->Parent(this);
        mTextures[1]->Pos(VEC2_ZERO);
    }

    mType = clumster;

    AddCollider(new CircleCollider(mTextures[0]->ScaledDimensions().x/2,false));
}

Clumster::~Clumster() {

}

void Clumster::Hit(PhysEntity* other){
    AudioManager::Instance()->PlaySFX("hit.wav",0,1);
    sPlayer->AddScore(15);
    Enemy::Hit(other);
}

void Clumster::Update() {
    if(!mDead){
        Translate(mDirection*mSpeed*mTimer->DeltaTime());

        Vector2 pos =Pos();
        if(pos.x < 0){
            pos.x = 0;
            mDirection.x *= -1;
        }else if(pos.x > Graphics::Instance()->SCREEN_WIDTH){
            pos.x = Graphics::Instance()->SCREEN_WIDTH;
            mDirection.x *= -1;
        }

        if(pos.y < 0){
            pos.y = 0;
            mDirection.y *= -1;
        }else if(pos.y > Graphics::Instance()->SCREEN_HEIGHT){
            pos.y = Graphics::Instance()->SCREEN_HEIGHT;
            mDirection.y *= -1;
        }

        Pos(pos);
    }
}
