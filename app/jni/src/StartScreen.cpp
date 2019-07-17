#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

    SDL_Log("ancho %d",Graphics::Instance()->SCREEN_WIDTH);
    SDL_Log("largo %d",Graphics::Instance()->SCREEN_HEIGHT );

	mFondo[0] = new Texture("inicio2.png",Graphics::Instance()->SCREEN_WIDTH,Graphics::Instance()->SCREEN_HEIGHT);
	mFondo[0]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH/2,Graphics::Instance()->SCREEN_HEIGHT/2));
	mFondo[1] = new Texture("KarelMan2.png");
	mFondo[1]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH/2,Graphics::Instance()->SCREEN_HEIGHT/2));
}

StartScreen::~StartScreen() {
	delete mFondo[0];
	mFondo[0]= NULL;

	delete mFondo[1];
	mFondo[1]= NULL;
}



void StartScreen::Update() {

}

void StartScreen::Render() {
	mFondo[0]->Render();
	mFondo[1]->Render();
}
