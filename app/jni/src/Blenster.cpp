// Created by kevin20012 on 01/04/2019.
#include "Blenster.h"

Blenster::Blenster(bool especial)
	: Enemy()
{
	mTextures[0] = new Texture("blenster2.png",80,80);
	mTextures[0]->Parent(this);
	mTextures[0]->Pos(VEC2_ZERO);

	mSpecial = especial;
	if(mSpecial){
        mTextures[1] = new Texture("special.png",80,80);
        mTextures[1]->Parent(this);
        mTextures[1]->Pos(VEC2_ZERO);
	}


	mType = blenster;

	AddCollider(new CircleCollider(mTextures[0]->ScaledDimensions().x/2,false));
}

Blenster::~Blenster() {

}

void Blenster::Hit(PhysEntity * other){
	AudioManager::Instance()->PlaySFX("hit.wav", 0, 1);
	sPlayer->AddScore(10);
	Enemy::Hit(other);
}

void Blenster::Update() {
    if(!mDead) {
        //Translate(mDirection*mSpeed*mTimer->DeltaTime());
        Vector2 aux = sPlayer->Pos() - Pos();
        Translate(aux.Normalized() * mSpeed * mTimer->DeltaTime());

        Vector2 pos = Pos();

        pos.x = Clamp(pos.x, 0, Graphics::Instance()->SCREEN_WIDTH);
        pos.y = Clamp(pos.y, 0, Graphics::Instance()->SCREEN_HEIGHT);

        Pos(pos);
    }
}
