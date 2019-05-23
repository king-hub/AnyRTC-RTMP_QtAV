#include "QtD3d9Player.h"
#include <QtWidgets/QApplication>

#include "D3dPlay.h"
#include<d3d9.h>
#include <process.h>




extern "C"
{
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

//D3D9相关参数
static LPDIRECT3DSURFACE9  g_pDirectSurface9 = NULL;
static LPDIRECT3D9		   g_pD3d;
static LPDIRECT3DDEVICE9   g_pD3dDev;
static D3DPRESENT_PARAMETERS g_D3dParam;
static RECT                g_rcWin = { 0 };
static RECT				   g_lastRect = {0};
static RECT				   g_contentRect = {0};
static HWND			       g_pPlayWnd = NULL;
static D3DFORMAT           g_D3dFmt;

//ffmpeg相关参数
static AVFormatContext *g_pAvFmtCtx = NULL;
static AVCodecContext  *g_pAvCodecCtx = NULL;
static int              g_VideoIndex = -1;
static AVCodec         *g_pAvCodec = NULL;
static HANDLE           g_hVideoRenderThread = NULL;
static AVPixelFormat    g_AVFix;

QtD3d9Player *w;


#include <QDebug>


unsigned int _stdcall VideoRenderThread(LPVOID p)
{
	//分配一个AVPacket并且填充字段默认值
	AVPacket *pkt = av_packet_alloc();

	AVFrame  *pFrame = av_frame_alloc();
	AVFrame  *pFrameYUV = av_frame_alloc();

	RECT rcClient = { 0 };
	//获取显示窗口的矩形区域

	SwsContext* img_convert_ctx = NULL;

	while (true)
	{
		if (av_read_frame(g_pAvFmtCtx, pkt) == 0)
		{
			if (pkt->stream_index == g_VideoIndex)
			{
				if (avcodec_send_packet(g_pAvCodecCtx, pkt) == 0)
				{
					if (avcodec_receive_frame(g_pAvCodecCtx, pFrame) == 0)
					{
						/*读取一帧成功，显示图像*/

						//防止窗口变化获取窗口大小
						GetClientRect(g_pPlayWnd, &rcClient);
						//RECT rt = { 0 };
						//GetWindowRect(g_pPlayWnd, &rt);
						
						if (rcClient.left == rcClient.bottom == rcClient.right == rcClient.top == 0
							|| rcClient.left != g_rcWin.left
							|| rcClient.top != g_rcWin.top
							|| rcClient.right != g_rcWin.right
							|| rcClient.bottom != g_rcWin.bottom)
						{
							//InvalidateRect(g_pPlayWnd, &rcClient, FALSE);

							//qDebug() << "video: " << rt.left << " " << rt.right << " " << rt.top << " " << rt.bottom
							//<<  "   window: " << rcClient.left << " " << rcClient.right << " " << rcClient.top << " " << rcClient.bottom;

							//qDebug() << "window:  w=" << rt.right - rt.left << "h=" << rt.bottom - rt.top;
							qDebug() << "client:  w=" << rcClient.right - rcClient.left << "h=" << rcClient.bottom - rcClient.top;
							qDebug() << "qt    :  w=" << w->width() << "h=" << w->height();
							qDebug() << "frame :  w=" << pFrame->width << "h=" << pFrame->height;

							g_rcWin = rcClient;

							long W = g_rcWin.right - g_rcWin.left;
							long H = g_rcWin.bottom - g_rcWin.top;
							float r = 16.0 / 9.0;
							if ((float)W/H > r)
							{
								g_contentRect.top = g_rcWin.top;
								g_contentRect.bottom = g_rcWin.bottom;
								float w = r * H;
								g_contentRect.left = (W-w)/2;
								g_contentRect.right = g_contentRect.left + w;
							}
							else
							{
								g_contentRect.left = g_rcWin.left;
								g_contentRect.right = g_rcWin.right;
								float h = W / r;
								g_contentRect.top = (H - h) / 2;
								g_contentRect.bottom = g_contentRect.top + h;
							}

							

							sws_freeContext(img_convert_ctx);
							//img_convert_ctx = sws_getContext(g_pAvCodecCtx->width, g_pAvCodecCtx->height
							//	, g_pAvCodecCtx->pix_fmt, g_rcWin.right - g_rcWin.left, g_rcWin.bottom - g_rcWin.top
							//	, g_AVFix, SWS_BICUBIC, NULL, NULL, NULL);
							img_convert_ctx = sws_getContext(pFrame->width, pFrame->height
								, (AVPixelFormat)pFrame->format, g_contentRect.right - g_contentRect.left, g_contentRect.bottom - g_contentRect.top
								, g_AVFix, SWS_BICUBIC, NULL, NULL, NULL);

							if (g_pDirectSurface9)
							{
								g_pDirectSurface9->Release();
								g_pDirectSurface9 = NULL;
							}
						}

						if (!g_pDirectSurface9) 
						{
							// create surface and resize backbuffer
						/*	if (FAILED(g_pD3dDev->CreateOffscreenPlainSurface(g_rcWin.right - g_rcWin.left
								, g_rcWin.bottom - g_rcWin.top, (D3DFORMAT)g_D3dFmt,
								D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL)))*/
								if (FAILED(g_pD3dDev->CreateOffscreenPlainSurface(g_contentRect.right - g_contentRect.left
									, g_contentRect.bottom - g_contentRect.top, (D3DFORMAT)g_D3dFmt,
									D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL)))
							{
								return 0;
							}
						}
						g_pD3dDev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 255), 1.0f, 0);
						//锁定纹理矩形区域
						D3DLOCKED_RECT d3d_rect;
						g_pDirectSurface9->LockRect(&d3d_rect, NULL, D3DLOCK_DISCARD);

						
						
						//int n = avpicture_get_size(AV_PIX_FMT_YUV420P, g_rcWin.right - g_rcWin.left, g_rcWin.bottom - g_rcWin.top);					
						//memset(d3d_rect.pBits, 0, n);


						pFrameYUV->data[0] = (uint8_t*)d3d_rect.pBits;
						pFrameYUV->linesize[0] = d3d_rect.Pitch;
						
						//AVFrame *tFrame = av_frame_alloc();
						//int numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P, g_contentRect.right - g_contentRect.left, g_contentRect.bottom - g_contentRect.top);
						//uint8_t* buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
						//avpicture_fill((AVPicture *)tFrame, buffer, AV_PIX_FMT_YUV420P, g_contentRect.right - g_contentRect.left, g_contentRect.bottom - g_contentRect.top);

						//sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize
						//	, 0, g_pAvCodecCtx->height,
						//	tFrame->data, tFrame->linesize);
						//qDebug() << "########### " << tFrame->linesize[0] << d3d_rect.Pitch;

						//int w = g_rcWin.right - g_rcWin.left;
						//int h = g_rcWin.bottom - g_rcWin.top;

						//if ( (float)w/h > (16.0/9.0))
						//{
						//	//拷贝至行中间
						//	for (int i = 0; i < h; i++)
						//	{
						//		
						//	}
						//}
						//else
						//{
						//	//拷贝至列中间
						//}


						//av_frame_free(&tFrame);
						

						sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize
							, 0, pFrame->height,
							pFrameYUV->data, pFrameYUV->linesize);


						g_pDirectSurface9->UnlockRect();

						//没起作用???
						

						IDirect3DSurface9 *pBackBuffer = NULL;
						
						//g_pD3dDev->BeginScene();
						if (SUCCEEDED(g_pD3dDev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer))) 
						{
							if (pBackBuffer) 
							{
								if (SUCCEEDED(g_pD3dDev->StretchRect(g_pDirectSurface9, NULL, pBackBuffer, NULL, D3DTEXF_LINEAR))) 
								{
									//D3DRECT rt;
									//g_pD3dDev->Present(NULL, &g_rcWin, NULL, NULL);
									g_pD3dDev->Present(NULL, &g_contentRect, NULL, NULL);
								}
								

								pBackBuffer->Release();
							}

						}
					

						Sleep(40);
					}
				}
			}
		}
	}
	return 0;
}

void Play()
{

	//初始化libavformat并且注册所有的复用和解复用协议
	av_register_all();

	//分配一个AVFormatContext
	g_pAvFmtCtx = avformat_alloc_context();
	//rtmp://live.hkstv.hk.lxdns.com/live/hks1
	//rtmp://202.69.69.180:443/webcast/bshdlive-pc
	if (avformat_open_input(&g_pAvFmtCtx, "rtmp://live.hkstv.hk.lxdns.com/live/hks1", NULL, NULL) < 0)
		//if (avformat_open_input(&g_pAvFmtCtx, "rtmp://202.69.69.180:443/webcast/bshdlive-pc", NULL, NULL) < 0)
	{
		//打开输入文件失败
		return;
	}

	if (avformat_find_stream_info(g_pAvFmtCtx, NULL) < 0)
	{
		//找不到流的相关信息
		return;
	}

	for (unsigned int i = 0; i < g_pAvFmtCtx->nb_streams; i++)
	{
		if (g_pAvFmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			g_VideoIndex = i;
		}
	}

	//分配一个AVCodecContext并且给字段填充默认的值
	g_pAvCodecCtx = avcodec_alloc_context3(NULL);

	//填充编解码器上下字段值基于提供的编解码器参数
	if (avcodec_parameters_to_context(g_pAvCodecCtx,g_pAvFmtCtx->streams[g_VideoIndex]->codecpar) < 0)
	{
		//填充参数出错
		return;
	}

	//找到一个与编码器Id匹配并且已注册的解码器
	g_pAvCodec = avcodec_find_decoder(g_pAvCodecCtx->codec_id);
	if (g_pAvCodec == NULL)
	{
		//解码器没找到
		return;
	}

	//用给定的编解码器去初始化编解码器上下文参数
	if (avcodec_open2(g_pAvCodecCtx, g_pAvCodec, NULL) < 0)
	{
		//上下文初始化失败
		return;
	}

	//Direct3d COM接口
	g_pDirectSurface9 = (LPDIRECT3DSURFACE9)calloc(1, sizeof(IDirect3DSurface9));
	//创建Direct3D9对象
	g_pD3d = Direct3DCreate9(D3D_SDK_VERSION);

	//描述显示模式的结构体参数
	D3DDISPLAYMODE d3dmode = { 0 };
	ZeroMemory(&g_D3dParam, sizeof(D3DPRESENT_PARAMETERS));
	g_pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmode);

	g_D3dParam.BackBufferFormat = D3DFMT_UNKNOWN;       //缓冲区格式
	g_D3dParam.BackBufferCount = 1;
	//g_D3dParam.BackBufferWidth = g_pAvCodecCtx->width;
	//g_D3dParam.BackBufferHeight = g_pAvCodecCtx->height;
	g_D3dParam.BackBufferWidth = 1920;
	g_D3dParam.BackBufferHeight = 1080;

	g_D3dParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	g_D3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3dParam.hDeviceWindow = g_pPlayWnd;
	g_D3dParam.Windowed = TRUE;
	g_D3dParam.EnableAutoDepthStencil = FALSE;
	g_D3dParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//创建一个设置去呈现显示适配器
	if (FAILED(g_pD3d->CreateDevice(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL, g_pPlayWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING
		, &g_D3dParam, &g_pD3dDev)))
	{
		//D3DERR_DEVICELOST, D3DERR_INVALIDCALL, D3DERR_NOTAVAILABLE, D3DERR_OUTOFVIDEOMEMORY
		return;
	}
	//创建一个屏幕之外的平面
	/*if (SUCCEEDED(g_pD3dDev->CreateOffscreenPlainSurface(1, 1, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
		D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL)))
	{
		g_D3dFmt = (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2');
		g_AVFix = AV_PIX_FMT_YUV420P;
	}*/
	if (SUCCEEDED(g_pD3dDev->CreateOffscreenPlainSurface(1, 1, D3DFMT_YUY2,
		D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL)))
	{
		g_D3dFmt = D3DFMT_YUY2;
		g_AVFix = AV_PIX_FMT_YUYV422;
		/*g_D3dFmt = (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2');
		g_AVFix = AV_PIX_FMT_YUV420P;*/
	}
	else if (SUCCEEDED(g_pD3dDev->CreateOffscreenPlainSurface(1, 1, D3DFMT_UYVY,
		D3DPOOL_DEFAULT, &g_pDirectSurface9, NULL)))
	{
		g_D3dFmt = D3DFMT_UYVY;
		g_AVFix = AV_PIX_FMT_YUYV422;
	}
	else
	{
		g_D3dFmt = D3DFMT_X8R8G8B8;
		g_AVFix = AV_PIX_FMT_YUYV422;
	}

	g_pDirectSurface9->Release();
	g_pDirectSurface9 = NULL;


	//启线程去做视频渲染，防止主线程窗口卡死
	g_hVideoRenderThread = (HANDLE)_beginthreadex(NULL, 0, VideoRenderThread, NULL, 0, NULL);
}
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QScrollArea area;
	//area.setAttribute(Qt::WA_TranslucentBackground, true);
	//area.setStyleSheet("QScrollArea{background-color: rgb(255, 255, 255, 0)};");
	
	QPushButton *pBtn = new QPushButton("button", &area);
	
	QLabel *plb = new QLabel("hello world");
	plb->setPixmap(QPixmap(R"(E:\2019\0423\smart-class4-all\SmartClassRoom\resource\Image\DefaultHd.png)"));
	plb->resize(100, 100);
	plb->setScaledContents(true);
	plb->setParent(&area);
	//plb->setAttribute(Qt::WA_TranslucentBackground, true);
	//plb->setStyleSheet("background-color: rgb(255, 255, 255, 0);");
	plb->show();
	plb->move(200, 0);


	area.setWidgetResizable(true);
	w = new QtD3d9Player();
	/*w->setAttribute(Qt::WA_PaintOnScreen, true);
	w->setAttribute(Qt::WA_NativeWindow, true);
	w->setAutoFillBackground(true);
	w->setPalette(Qt::darkGreen);*/
	//w->setAttribute(Qt::WA_TranslucentBackground, true);
	//w->setStyleSheet("QWidget{background-color: rgb(255, 255, 255, 0)};");
	//area.setWidget(w);
	w->resize(640, 480);
	w->show();
	//area.show();
	g_pPlayWnd = (HWND)w->winId();
	Play();

	return a.exec();
}
