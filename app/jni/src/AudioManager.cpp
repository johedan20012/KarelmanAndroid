#include "AudioManager.h"

AudioManager* AudioManager::sInstance = NULL;

AudioManager* AudioManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new AudioManager();
	}

	return sInstance;
}

void AudioManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

AudioManager::AudioManager() {

	mAssetMgr = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {

		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}

}

AudioManager::~AudioManager() {

	mAssetMgr = NULL;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops) {

	Mix_Music* music = mAssetMgr->GetMusic(filename);
	Mix_PlayMusic(music, loops);

}

void AudioManager::PauseMusic() {

	if (Mix_PlayingMusic() != 0) {
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic() {

	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel) {
	if(!Mix_Playing(channel)) Mix_PlayChannel(channel, mAssetMgr->GetSFX(filename), loops);
}