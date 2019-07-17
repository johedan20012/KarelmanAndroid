#include "ImputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance(){

	if (sInstance == NULL) {
		sInstance = new InputManager();
	}

	return sInstance;
}

void InputManager::Release(){

	delete sInstance;
	sInstance = NULL;
}

InputManager::InputManager() {
	for(int a=0; a< mNumButtons; a++){
		mGamepadButtons[a] = new Button( new Texture("ScreenGamepad/button1.png",100,100));
	}

    //mGamepadButtons[0]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH-100,Graphics::Instance()->SCREEN_HEIGHT-120));

	for(int a=0; a< mNumJoys; a++){
		mJoysticks[a] = new Joystick();
	}
	mJoysticks[0]->mText[0]->Pos(Vector2(150,Graphics::Instance()->SCREEN_HEIGHT-150));
	mJoysticks[0]->mText[1]->Pos(mJoysticks[0]->mText[0]->Pos());

    mJoysticks[1]->mText[0]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH - 150,Graphics::Instance()->SCREEN_HEIGHT-350));
    mJoysticks[1]->mText[1]->Pos(mJoysticks[1]->mText[0]->Pos());
}

InputManager::~InputManager() {
	for(int a=0; a< mNumButtons; a++){
		delete mGamepadButtons[a];
		mGamepadButtons[a] = NULL;
	}

	for(int a=0; a< mNumJoys; a++){
		delete mJoysticks[a];
		mJoysticks[a] = NULL;
	}
}

int InputManager::GetGamepadState(BUTTON boton) {

    return mGamepadButtons[boton]->GetButtonState();
}

Vector2 InputManager::GetJoystickState(int index) {
    return mJoysticks[index]->GetLocalPos() / mJoysticks[index]->GetRadio(); //Normalizo los valores de mi joystick de -1 a 1
}

int InputManager::TouchState(){
	return (SDL_GetTouchFinger(SDL_GetTouchDevice(0),0) != NULL) ? 1 : 0;
}

void InputManager::Update() {
    SDL_TouchID device = SDL_GetTouchDevice(0);
    int numTouch = SDL_GetNumTouchFingers(device);
    SDL_Finger* aux;
    SDL_Rect auxi;
    Vector2 touchPos;
    int mJoysTicksAct = 0,mButtAct = 0;
    bool consumido;

    for(int a = 1; a<=numTouch; a++) {
        aux = SDL_GetTouchFinger(device, a - 1);
        touchPos = intearVector(Vector2(aux->x*Graphics::Instance()->SCREEN_WIDTH,aux->y*Graphics::Instance()->SCREEN_HEIGHT));
        //SDL_Log("aux id %d",aux->id);
        consumido = false;
        for(int b=0; b<mNumJoys; b++) {
            if (mJoysticks[b]->mFingerID == aux->id) {
                mJoysticks[b]->mText[1]->Pos(obtainFixedPoint(mJoysticks[b]->mText[0]->Pos(), touchPos, mJoysticks[b]->GetRadio()));
                consumido = true;
                mJoysTicksAct = mJoysTicksAct | (1<<b);
                break;
            }
        }
        if(consumido)continue;
        for(int b=0; b< mNumButtons; b++) {
            if(mGamepadButtons[b]->mFingerID == aux->id){
                auxi = mGamepadButtons[b]->mText->GetRenderRect();
                if(PointInRect(touchPos, auxi)) {
                    mGamepadButtons[b]->mState = 1;
                    consumido = true;
                    break;
                }else{
                    mGamepadButtons[b]->mState = 0;
                    mGamepadButtons[b]->mFingerID = -1;
                }
                mButtAct = mButtAct | (1<<b);
            }
        }
        if(consumido)continue;
        for(int b=0; b< mNumButtons; b++) {
            if(mGamepadButtons[b]->mFingerID == -1) {
                auxi = mGamepadButtons[b]->mText->GetRenderRect();
                if (PointInRect(touchPos, auxi)) {
                    mGamepadButtons[b]->mFingerID = aux->id;
                    mGamepadButtons[b]->mState = 1;
                    consumido = true;
                    break;
                }
            }
        }
        if(consumido)continue;
        for (int b = 0; b < mNumJoys; b++) {
            if(mJoysticks[b]->mFingerID == -1) {
                auxi = mJoysticks[b]->mText[0]->GetRenderRect();
                if (PointInRect(touchPos, auxi)) {
                    mJoysticks[b]->mText[1]->Pos(obtainFixedPoint(mJoysticks[b]->mText[0]->Pos(), touchPos, mJoysticks[b]->GetRadio()));
                    mJoysticks[b]->mFingerID = aux->id;
                    break;
                }
            }
        }
    }

    for(int b=0; b<mNumJoys; b++) {
        if (mJoysticks[b]->mFingerID != -1 && !(mJoysTicksAct & (1<<b))) {
            aux = SDL_GetTouchFinger(device, mJoysticks[b]->mFingerID);
            if(aux != nullptr){
                touchPos = intearVector(Vector2(aux->x*Graphics::Instance()->SCREEN_WIDTH,aux->y*Graphics::Instance()->SCREEN_HEIGHT));
                mJoysticks[b]->mText[1]->Pos(obtainFixedPoint(mJoysticks[b]->mText[0]->Pos(), touchPos, mJoysticks[b]->GetRadio()));
            }else{
                mJoysticks[b]->mText[1]->Pos(mJoysticks[b]->mText[0]->Pos());
                mJoysticks[b]->mFingerID = -1;
            }
        }
    }

    for(int b=0; b<mNumButtons; b++){
        if(mGamepadButtons[b]->mFingerID != -1 && (mButtAct & (1<<b))){
            aux = SDL_GetTouchFinger(device, mJoysticks[b]->mFingerID);
            if(aux != nullptr){
                mGamepadButtons[b]->mState = 1;
            }else{
                mGamepadButtons[b]->mState = 0;
                mGamepadButtons[b]->mFingerID = -1;
            }
        }
    }


}

void InputManager::UpdatePrevInput() {
    for(int a=0; a< mNumButtons; a++){
        mGamepadButtons[a]->UpdatePrevInput();
    }
}

void InputManager::Render(){
    for(int a=0; a< mNumButtons; a++){
        mGamepadButtons[a]->Render();
    }

    for(int a=0; a< mNumJoys; a++){
        mJoysticks[a]->mText[0]->Render();
        mJoysticks[a]->mText[1]->Render();
    }
}