// Created by kevin20012 on 03/04/2019.

#ifndef _BUTTON_H
#define _BUTTON_H

#include "GameEntity.h"
#include "Texture.h"

class Button : public GameEntity{

public:

    int mFingerID;


    int mState,mPrevState;

    Texture* mText;

public:
    //Button();

    Button(Texture* texture = NULL);

    ~Button();

    int GetButtonState();

    void UpdatePrevInput();
    void Update();

    void Render();
};

#endif
