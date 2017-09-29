#pragma once
#include "SDL2\SDL.h"

class VideoPlayer
{
private:
	SDL_Window *screen;
	SDL_Renderer* sdlRenderer;
	SDL_Texture* sdlTexture;
public:
	VideoPlayer();
	~VideoPlayer();
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWidth, int nHeight);
	int PushFrame(unsigned char * data, int linesize);
};

