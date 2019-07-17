#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {

	if (sInstance == NULL) {

		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager() {

	mInput = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update() {


	switch (mCurrentScreen) {

	case start:

		mStartScreen->Update();
		if (mInput->TouchState() == 1) {

			mCurrentScreen = play;
			mPlayScreen->StartNewGame();
		}
		break;

	case play:

		mPlayScreen->Update();
		if (mPlayScreen->GameOver()) {

			mCurrentScreen = start;
		}
		break;
	}
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {
		
	case start:

		mStartScreen->Render();
		break;

	case play:

		mPlayScreen->Render();
		break;
	}
}