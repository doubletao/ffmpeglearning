#include "SDLVideoPlayer.h"
#include "VideoPlayer.h"

static VideoPlayer * StaticCast(void * pPlayer)
{
	return static_cast<VideoPlayer *>(pPlayer);
}

SDLVideoPlayer::SDLVideoPlayer()
	: m_wndPlayer(nullptr)
{
	m_wndPlayer = new VideoPlayer;
}


SDLVideoPlayer::~SDLVideoPlayer()
{
	if (m_wndPlayer)
	{
		delete StaticCast(m_wndPlayer);
		m_wndPlayer = nullptr;
	}
}

int SDLVideoPlayer::IntialWnd(unsigned int nFormat, int x, int y, int nWidth, int nHeight)
{
	return StaticCast(m_wndPlayer)->IntialWnd(nFormat, x, y, nWidth, nHeight);
}

int SDLVideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	return StaticCast(m_wndPlayer)->PushFrame(data, linesize);
}
