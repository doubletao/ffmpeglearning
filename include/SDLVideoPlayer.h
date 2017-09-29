#pragma once
#ifdef SDL_VIDEO_PLAYER_API
#define SDL_VIDEO_PLAYER_EXPORT __declspec(dllexport)
#else
#define SDL_VIDEO_PLAYER_EXPORT __declspec(dllimport)
#ifdef _DEBUG
#	pragma comment(lib, "SDLVideoPlayerD.lib")
#else
#	pragma comment(lib, "SDLVideoPlayerU.lib")
#endif
#endif // SDL_VIDEO_PLAYER_API

class SDL_VIDEO_PLAYER_EXPORT SDLVideoPlayer
{
private:
	void * m_wndPlayer;
public:
	SDLVideoPlayer();
	~SDLVideoPlayer();
public:
	int IntialWnd(unsigned int nFormat, int x, int y, int nWidth, int nHeight);
	int PushFrame(unsigned char * data, int linesize);
};
