// FFmpegLearning.cpp : 定义控制台应用程序的入口点。
//
#define SDL_MAIN_HANDLED  
#include "stdafx.h"
#include <assert.h>
#include "SDLVideoPlayer.h"
#include "SDL2\SDL.h"
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

int main()
{
	SDLVideoPlayer player;
	player.IntialWnd(SDL_PIXELFORMAT_ABGR8888, 960, 528);
	const int nSize = 100;
	SDL_Surface * surFace[nSize];
	char szFileName[256];
	for (size_t i = 0; i < nSize; i++)
	{
		memset(szFileName, 0, 256);
		SDL_snprintf(szFileName, 256, "C:\\Users\\dujiangtao\\Desktop\\bmp\\%d.bmp", i + 1);
		surFace[i] = SDL_LoadBMP(szFileName);
		if (!surFace[i])
		{
			printf("Could not load bmp- %s\n", SDL_GetError());
			assert(false);
		}
	}
	int nIndex = 0;
	while (nIndex < nSize)
	{
		player.PushFrame((unsigned char *)surFace[nIndex]->pixels, surFace[nIndex]->pitch);
		SDL_Delay(50);
		nIndex++;
	}
    return 0;
}

