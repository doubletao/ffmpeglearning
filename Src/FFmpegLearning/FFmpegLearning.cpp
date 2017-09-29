// FFmpegLearning.cpp : 定义控制台应用程序的入口点。
//
#define SDL_MAIN_HANDLED  
#include "stdafx.h"
#include <assert.h>
#include "SDLVideoPlayer.h"
#include "SDL2\SDL.h"
#include "FFmpegVADecoder.h"
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

int main()
{
	FFmpegVADecoder codec;
	codec.OpenFile("F:\\Media\\超人总动员.AVI");
	int nWidth;
	int nHeight;
	AVPixelFormat emPixFmt;
	codec.GetVideoBasicInfo(nWidth, nHeight, emPixFmt);
	//根据视频信息初始化窗口
	SDLVideoPlayer player;
	player.IntialWnd(SDL_PIXELFORMAT_IYUV, 500, 300, nWidth, nHeight);
	unsigned char * pData = nullptr;
	int nLineSize = 0;
	while (codec.DecodeOneFrame(pData, nLineSize))
	{
		player.PushFrame(pData, nLineSize);
		SDL_Delay(20);
	}
	system("pause");
    return 0;
}

