#pragma once
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
//#include "libswscale\swscale.h"
}

class VADecoder
{
private:
	int nVideoIndex;
	AVFormatContext	* pFormatCtx;
	AVCodecContext * pCodecCtx;
	AVCodecParameters * pCodecParm;
	AVCodec * pCodec;
	AVPacket * packet;
	AVFrame	* pFrame;
public:
	VADecoder();
	~VADecoder();
public:
	int OpenFile(const char * szFilePath);
	int GetVideoBasicInfo(int & nWidth, int & nHeight, AVPixelFormat & emPixFmt);
	int DecodeOneFrame(unsigned char **& data, int *& linesize);
	int CloseFile();
};

