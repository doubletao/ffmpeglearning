#include "FFmpegVADecoder.h"
#include "VADecoder.h"

static VADecoder * StaticCast(void * pDecoder)
{
	return static_cast<VADecoder *>(pDecoder);
}

FFmpegVADecoder::FFmpegVADecoder()
	: m_pDecoder(nullptr)
{
	m_pDecoder = new VADecoder;
}


FFmpegVADecoder::~FFmpegVADecoder()
{
	delete StaticCast(m_pDecoder);
	m_pDecoder = nullptr;
}

int FFmpegVADecoder::OpenFile(const char * szFilePath)
{
	return StaticCast(m_pDecoder)->OpenFile(szFilePath);
}

int FFmpegVADecoder::GetVideoBasicInfo(int & nWidth, int & nHeight, AVPixelFormat & emPixFmt)
{
	return StaticCast(m_pDecoder)->GetVideoBasicInfo(nWidth, nHeight, emPixFmt);
}

int FFmpegVADecoder::DecodeOneFrame(unsigned char **& data, int *& linesize)
{
	return StaticCast(m_pDecoder)->DecodeOneFrame(data, linesize);
}
