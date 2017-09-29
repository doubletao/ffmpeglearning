#include "VADecoder.h"
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
//#pragma comment(lib, "avdevice.lib")
//#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avutil.lib")
//#pragma comment(lib, "postproc.lib")
//#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")

VADecoder::VADecoder()
	: nVideoIndex(-1)
	, pFormatCtx(nullptr)
	, pCodecCtx(nullptr)
	, pCodecParm(nullptr)
	, pCodec(nullptr)
	, packet(nullptr)
	, pFrame(nullptr)
	, pFrameYUV(nullptr)
	, outerbuffer(nullptr)
{
}

VADecoder::~VADecoder()
{
	CloseFile();
}

int VADecoder::OpenFile(const char * szFilePath)
{
	//注册所有支持的格式
	av_register_all();
	//网络组件的初始化（非必须）,应该是解网络流的时候在用
	//avformat_network_init();
	//创建解封装器
	pFormatCtx = avformat_alloc_context();
	if (pFormatCtx)
	{
		//解封装
		if (avformat_open_input(&pFormatCtx, szFilePath, nullptr, nullptr) == 0)
		{
			//得到流数据
			if (avformat_find_stream_info(pFormatCtx, nullptr) >= 0)
			{
				//查找视频流
				nVideoIndex = -1;
				for (size_t i = 0; i < pFormatCtx->nb_streams; i++)
				{
					if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
					{
						nVideoIndex = (int)i;
						break;
					}
				}
				if (nVideoIndex > -1)
				{
					//根据编码格式查找解码器
					//先拿到解码参数
					pCodecParm = pFormatCtx->streams[nVideoIndex]->codecpar;
					if (pCodecParm)
					{
						//查找解码器
						pCodec = avcodec_find_decoder(pCodecParm->codec_id);
						if (pCodec)
						{
							//解码参数转成解码上下文
							pCodecCtx = avcodec_alloc_context3(pCodec);
							avcodec_parameters_to_context(pCodecCtx, pCodecParm);
							if (pCodecCtx)
							{
								//根据解码上下文打开解码器
								if (avcodec_open2(pCodecCtx, pCodec, nullptr) == 0)
								{
									outerbuffer = (unsigned char *)av_malloc(av_image_get_buffer_size(pCodecCtx->pix_fmt,
										pCodecCtx->width, pCodecCtx->height, 1));
									pFrameYUV = av_frame_alloc();
#if 0
									//颜色空间转换及缩放逻辑，先跳过
									unsigned char * outerbuffer = (unsigned char *)av_malloc(av_image_get_buffer_size(pCodecCtx->pix_fmt,
										pCodecCtx->width, pCodecCtx->height, 1));
									AVFrame	* pFrameYUV = nullptr;
									av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, outerbuffer, pCodecCtx->pix_fmt,
										pCodecCtx->width, pCodecCtx->height, 1);
									SwsContext * imgConvertCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
										pCodecCtx->width, pCodecCtx->height, )
#endif
										return 1;
								}
								else
								{
									printf("failed to open codec\n");
								}
							}
							else
							{
								printf("failed to find codec\n");
							}
						}
						else
						{
							printf("failed to get codexcontext\n");
						}
					}
					else
					{
						printf("failed to get codecparam\n");
					}
				}
				else
				{
					printf("failed to find video stream\n");
				}
			}
			else
			{
				printf("failed to find stream\n");
			}
		}
		else
		{
			printf("failed to open input\n");
		}
	}
	else
	{
		printf("failed to alloc context\n");
	}
	CloseFile();
	return 0;
}

int VADecoder::GetVideoBasicInfo(int & nWidth, int & nHeight, AVPixelFormat & emPixFmt)
{
	if (pCodecCtx)
	{
		nWidth = pCodecCtx->width;
		nHeight = pCodecCtx->height;
		emPixFmt = pCodecCtx->pix_fmt;
		return 1;
	}
	else
	{
		printf("file not open or open failed\n");
		CloseFile();
		return 0;
	}
}

int VADecoder::DecodeOneFrame(unsigned char *& data, int & linesize)
{
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	pFrame = av_frame_alloc();
	if (pFormatCtx && packet && nVideoIndex > -1)
	{
		while (true)
		{
			if (av_read_frame(pFormatCtx, packet) < 0)
			{
				//没读到，直接返回（可能是文件尾）
				return 0;
			}
			if (packet->stream_index != nVideoIndex)
			{
				//找出视频流
				continue;
			}
			//解码
			if (avcodec_send_packet(pCodecCtx, packet) == 0)
			{
				int nRet = -1;
				if ((nRet = avcodec_receive_frame(pCodecCtx, pFrame)) == 0)
				{
					//linesize = pFrame->linesize[0];
					//data = pFrame->data[0];

					//在这把颜色空间转换给做了，转成RGB的
					av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, outerbuffer, pCodecCtx->pix_fmt,
						pCodecCtx->width, pCodecCtx->height, 1);
					SwsContext * imgConvertCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
						pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
					sws_scale(imgConvertCtx, pFrame->data, pFrame->linesize, 0, pFrame->height, pFrameYUV->data,
						pFrameYUV->linesize);

					data = pFrameYUV->data[0];
					linesize = pFrameYUV->linesize[0];
					return 1;
				}
				else
				{
					continue;
					switch (nRet) {
					case 0:
						break;
					case AVERROR_EOF:
						printf("the decoder has been fully flushed,\
                               and there will be no more output frames.\n");
						break;

					case AVERROR(EAGAIN):
						printf("Resource temporarily unavailable\n");
						break;

					case AVERROR(EINVAL):
						printf("Invalid argument\n");
						break;
					default:
						break;
					}
					printf("failed to receive frame\n");
				}
			}
			else
			{
				printf("falied to send packet\n");
			}
		}
	}
	else
	{
		printf("file not open or open failed\n");
	}
	CloseFile();
	return 0;
}

int VADecoder::CloseFile()
{
	nVideoIndex = -1;
	if (pFrame)
	{
		av_frame_free(&pFrame);
	}
	if (packet)
	{
		av_packet_free(&packet);
	}
	if (pCodecCtx)
	{
		avcodec_close(pCodecCtx);
	}
	if (pFormatCtx)
	{
		avformat_free_context(pFormatCtx);
	}
	if (pFrameYUV)
	{
		av_frame_free(&pFrameYUV);
	}
	return 1;
}
