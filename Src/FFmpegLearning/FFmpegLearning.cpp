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
	codec.OpenFile("F:\\Media\\全民超人汉考克.威尔. 史密斯.查理兹. 塞隆.杰森. 贝特曼.2008.[1280x704高清晰版].rmvb");
	int nWidth;
	int nHeight;
	AVPixelFormat emPixFmt;
	codec.GetVideoBasicInfo(nWidth, nHeight, emPixFmt);
	//根据视频信息初始化窗口
	SDLVideoPlayer player;
	player.IntialWnd(SDL_PIXELFORMAT_IYUV, 500, 300, nWidth, nHeight);
	uint8_t ** pData = nullptr;
	int * nLineSize = nullptr;
	while (codec.DecodeOneFrame(pData, nLineSize))
	{
#if 0
		FILE * file;
		fopen_s(&file, "a.yuv", "wb+");
		if (file)
		{
			int y_size = nWidth * nHeight;
			fwrite(pData[0], 1, y_size, file);    //Y 
			fwrite(pData[1], 1, y_size / 4, file);  //U
			fwrite(pData[2], 1, y_size / 4, file);  //V
			fclose(file);
		}
#endif
		player.PushYUVFrame(pData, nLineSize);
		SDL_Delay(40);
	}
	system("pause");
    return 0;
}

