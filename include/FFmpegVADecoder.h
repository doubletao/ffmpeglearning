#pragma once
#ifdef FFMPEG_VA_DECODER_API
#define FFMPEG_VA_DECODER_API_EXPORT __declspec(dllexport)
#else
#define FFMPEG_VA_DECODER_API_EXPORT __declspec(dllimport)
#ifdef _DEBUG
#	pragma comment(lib, "FFMpegDecoderD.lib")
#else
#	pragma comment(lib, "FFMpegDecoderU.lib")
#endif
#endif // FFMPEG_VA_DECODER_API
#include "libavutil\pixfmt.h"

class FFMPEG_VA_DECODER_API_EXPORT FFmpegVADecoder
{
private:
	void * m_pDecoder;
public:
	FFmpegVADecoder();
	~FFmpegVADecoder();
public:
	int OpenFile(const char * szFilePath);
	int GetVideoBasicInfo(int & nWidth, int & nHeight, AVPixelFormat & emPixFmt);
	int DecodeOneFrame(unsigned char **& data, int *& linesize);
};
