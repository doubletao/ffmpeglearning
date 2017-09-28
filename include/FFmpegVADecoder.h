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

class FFMPEG_VA_DECODER_API_EXPORT FFmpegVADecoder
{
public:
	FFmpegVADecoder();
	~FFmpegVADecoder();
};

