#include "VideoPlayer.h"
#include <stdio.h>
#include <assert.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

VideoPlayer::VideoPlayer()
	: screen(NULL)
	, sdlRenderer(NULL)
	, sdlTexture(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) 
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		assert(false);
	}
}


VideoPlayer::~VideoPlayer()
{
	SDL_Quit();
}

int VideoPlayer::IntialWnd(unsigned int nFormat, int nWidth, int nHeight)
{
	//先创建screen
	screen = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		nWidth, nHeight, SDL_WINDOW_OPENGL);
	if (!screen) 
	{
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}

	//创建渲染器
	sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	//IYUV: Y + U + V  (3 planes)
	//YV12: Y + V + U  (3 planes)
	if (!sdlRenderer)
	{
		printf("SDL: could not create renderer - exiting:%s\n", SDL_GetError());
		return -1;
	}
	//创建纹理
	sdlTexture = SDL_CreateTexture(sdlRenderer, nFormat, SDL_TEXTUREACCESS_STREAMING, nWidth, nHeight);
	if (!sdlTexture)
	{
		printf("SDL: could not create texture - exiting:%s\n", SDL_GetError());
		return -1;
	}

	return 1;
}

int VideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	//将数据刷出来
	SDL_UpdateTexture(sdlTexture, NULL, data, linesize);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_RenderPresent(sdlRenderer);
	return 1;
}
