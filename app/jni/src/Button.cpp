// Created by kevin20012 on 03/04/2019.

#include "Button.h"

Button::Button(Texture* texture){
    mText = (texture != NULL) ? texture: new Texture("button1.png");
    mText->Parent(this);
    mText->Pos(VEC2_ZERO);

    mFingerID = -1;
    mState = mPrevState = 0;
}

Button::~Button(){
    delete mText;
    mText = NULL;
}

int Button::GetButtonState() {
    return (mPrevState << 1) + mState;
}

void Button::UpdatePrevInput(){
    mPrevState = mState;
    mState = 0;
    if(mPrevState + mState == 0) {
        mFingerID = -1;
    }
}

void Button::Update() {
    if(mFingerID == -1){ //Tomo el primer touch que encuentre
        //Buscar un touch que este sobre mi
            //Encontre un touch que esta sobre mi
                //mState = 1;
                //mFingerID = el id del touch;
                //Return;
    }else{
        //Buscar mi touch si existe
        // Exite
            //mState = 1;
        //No existe
            //mState = 0;
            //mFingerId = -1;
    }
}

void Button::Render() {
    mText->Render();
}
