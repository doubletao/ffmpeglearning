#include "SDLVideoPlayer.h"
#include "VideoPlayer.h"

int screen_w, screen_h;

VideoPlayer * StaticCast(void * pPlayer)
{
	return static_cast<VideoPlayer *>(pPlayer);
}

SDLVideoPlayer::SDLVideoPlayer()
	: m_wndPlayer(NULL)
{
	m_wndPlayer = new VideoPlayer;
}


SDLVideoPlayer::~SDLVideoPlayer()
{
	if (m_wndPlayer)
	{
		delete StaticCast(m_wndPlayer);
		m_wndPlayer = NULL;
	}
}

int SDLVideoPlayer::IntialWnd(unsigned int nFormat, int nWidth, int nHeight)
{
	return StaticCast(m_wndPlayer)->IntialWnd(nFormat, nWidth, nHeight);
}

int SDLVideoPlayer::PushFrame(unsigned char * data, int linesize)
{
	return StaticCast(m_wndPlayer)->PushFrame(data, linesize);
}
