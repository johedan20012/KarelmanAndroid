#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>

class Graphics {

public:
	SDL_Rect gScreenRect = { 0, 0, 320, 240 };
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 876;
	//static const int SCREEN_WIDTH = 1024;
	//static const int SCREEN_HEIGHT = 876; /// 876
	const char* WINDOW_TITTLE = "Galaga";

private:
	static Graphics* sInstance;
	static bool sInitialized;

	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;

public:
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
	
	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL , float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void DrawLine(float startX, float startY, float endX, float endY);

	void Render();

private:
	Graphics();
	~Graphics();

	bool Init();
};

#endif 


