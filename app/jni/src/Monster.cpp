// Created by kevin20012 on 01/04/2019.
#include "Monster.h"

Monster::Monster(bool especial)
    : Enemy()
{
    mTextures[0] = new Texture("monster2.png",80,90);
    mTextures[0]->Parent(this);
    mTextures[0]->Pos(VEC2_ZERO);

    mSpecial = especial;
    if(mSpecial) {
        mTextures[1] = new Texture("special.png", 80, 90);
        mTextures[1]->Parent(this);
        mTextures[1]->Pos(VEC2_ZERO);
    }

    mType = monster;

    mDelayChange = 1.0f;

    AddCollider(new CircleCollider(mTextures[0]->ScaledDimensions().x/2,false));
}

Monster::~Monster() {

}

void Monster::Hit(PhysEntity *other) {
    AudioManager::Instance()->PlaySFX("hit.wav",0,1);
    sPlayer->AddScore(25);
    Enemy::Hit(other);
}

void Monster::Update() {
    if(!mDead){
        Translate(mDirection*mSpeed*mTimer->DeltaTime());

        Vector2 pos =Pos();
        if(pos.x < 0){
            pos.x = 0;
        }else if(pos.x > Graphics::Instance()->SCREEN_WIDTH){
            pos.x = Graphics::Instance()->SCREEN_WIDTH;
        }

        if(pos.y < 0){
            pos.y = 0;
        }else if(pos.y > Graphics::Instance()->SCREEN_HEIGHT){
            pos.y = Graphics::Instance()->SCREEN_HEIGHT;
        }

        Pos(pos);

        mCurrentTime += Timer::Instance()->DeltaTime();
        if(mCurrentTime >= mDelayChange){
            mCurrentTime = 0;
            int degrees = rand() % 360;
            Vector2 aux = VEC2_UP;
            mDirection = RotateVector(aux,degrees);
        }
    }
}