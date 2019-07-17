#include "PlayScreen.h"

PlayScreen::PlayScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	//mAudio = AudioManager::Instance();

	mLevel = NULL;

	mPlayer = NULL;
}

PlayScreen::~PlayScreen() {

	mTimer = NULL;
	mInput = NULL;
	//mAudio = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;

}


void PlayScreen::StartNewGame() {
    //SDL_Log("Inicie un nuevo juego");
	if(mPlayer != NULL){
        delete mPlayer;
    }
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
	mPlayer->Active(true);

    if(mLevel != NULL){
        delete mLevel;
    }
    mLevel = new Level(mPlayer);

}

bool PlayScreen::GameOver() {

	return (mLevel->State() == Level::gameover);
}

void PlayScreen::Update() {

	mLevel->Update();
}

void PlayScreen::Render() {

	mLevel->Render();

    if(mLevel->State() == Level::running) {
        mInput->Render();
    }
}