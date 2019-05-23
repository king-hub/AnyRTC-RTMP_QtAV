#include "QtLive.h"
#include <QDebug>
#include <VideoFormat.h>
#include <VideoFrame.h>
#include <VideoRenderer.h>
#include <QVBoxLayout>
#include <QLabel>
#include <qscrollarea.h>
#include <qrgb.h>

#include <QGraphicsView>
#include <qgraphicsscene.h>
#include <qgraphicsproxywidget.h>

QtLive::QtLive(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	qRegisterMetaType<FrameRef>("FrameRef");

	/*
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_GraphicsItem;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_GLWidget;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_GDI;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_Direct2D;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_XV;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_X11;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_GLWidget2;
extern Q_AVWIDGETS_EXPORT VideoRendererId VideoRendererId_OpenGLWidget;
	*/
	QtAV::Widgets::registerRenderers();
	m_vo = new QtAV::VideoOutput(QtAV::VideoRendererId_OpenGLWidget,this);
	//m_vo->widget()->resize(666, 666);
	//QScrollArea *pArea = new QScrollArea();
	//pArea->setWidget(m_vo->widget());
	//m_vo->widget()->installEventFilter(this);
	//pMask = new QWidget();
	//pMask->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//pMask->setAttribute(Qt::WA_TranslucentBackground);
	//pMask->setPalette(pal);
	
	if (m_vo->widget())
	{//pRenderW = new QtAV::GLWidgetRenderer2();		
		
	  /*QGraphicsView *pView = new QGraphicsView();
		QGraphicsScene *pScene = new QGraphicsScene();
		pView->setScene(pScene);
		pScene->addWidget(m_vo->widget());*/

		QVBoxLayout *pVLayout = new QVBoxLayout();
		pVLayout->setMargin(0);
		pVLayout->addWidget(m_vo->widget());
		ui.widget->setLayout(pVLayout);

		QVBoxLayout *pVLayout1 = new QVBoxLayout();
		QLabel *plb = new QLabel("Hello World");
		plb->setStyleSheet("QLabel{font:19pt;color:darkgreen}");
		QPushButton *pBtn = new QPushButton("XXOO");
		//plb->setAttribute(Qt::WA_TranslucentBackground, true);
		//pBtn->setAutoFillBackground(true);
		pBtn->setFixedSize(200, 100);
		
		pBtn->setStyleSheet("QPushButton{background:transparent; color:green; border:2px solid blue ;font:19pt}");
		pVLayout1->addWidget(plb, 0, Qt::AlignCenter);
		pVLayout1->addWidget(pBtn, 0, Qt::AlignHCenter);
		//pVLayout->addStretch();
		QFrame *w = new QFrame();
		w->setStyleSheet("QFrame{background-color:gray;border-radius:15px;");
		w->resize(300, 300);
		/*w->setPalette(Qt::darkBlue);
		w->setAutoFillBackground(true);*/
		//w->show();
			//w->setLayout(pVLayout1);
		m_vo->widget()->setLayout(pVLayout1);
		//pMask->show();
	}
	/*QtAV::VideoFormat vFmt(QtAV::VideoFormat::Format_YUV420P);
	QtAV::VideoFrame vFrame(1111, 1111, vFmt);*/
	
	m_pAVRtmplayer = nullptr;
	connect(ui.pushButton, &QPushButton::clicked, this, &QtLive::onBtnClicked);
}

void QtLive::OnFrame(FrameRef frame)
{
	/*QMetaObject::invokeMethod(this, "showFrame",
		Qt::QueuedConnection,Q_ARG(FrameRef, frame));*/
	showFrame(frame);
	//qApp->processEvents();
}

void QtLive::showFrame(FrameRef frame)
{
	QtAV::VideoFormat vFmt(QtAV::VideoFormat::Format_YUV420P);
	QtAV::VideoFrame vFrame(frame.width, frame.height, vFmt, QByteArray());
	vFrame.setDisplayAspectRatio(16.0 / 9.0);
	quint8 *planes[] = { reinterpret_cast<quint8 *>(frame.yData),
		reinterpret_cast<quint8 *>(frame.uData),
		reinterpret_cast<quint8 *>(frame.vData) };
	vFrame.setBits(planes);
	int linesize[] = { frame.yStride, frame.uStride, frame.vStride };
	vFrame.setBytesPerLine(linesize);
	//QtAV::VideoRenderer *pRender = pRenderW;
	m_vo->receive(vFrame);
}

void QtLive::onBtnClicked()
{
	if (m_pAVRtmplayer == NULL) {
		m_pAVRtmplayer = RTMPGuester::Create(*this);
		m_pAVRtmplayer->SetFrameReciver(this);
		ui.lineEdit;
		m_pAVRtmplayer->StartRtmpPlay(ui.lineEdit->text().toLocal8Bit().data(), 
			(void *)ui.widget->winId());
		
	}
	else {
		m_pAVRtmplayer->StopRtmpPlay();
		RTMPGuester::Destory(m_pAVRtmplayer);
		m_pAVRtmplayer = NULL;
	}
}

void QtLive::resizeEvent(QResizeEvent * e)
{

	
	return QWidget::resizeEvent(e);
}

void QtLive::moveEvent(QMoveEvent * e)
{
	//pMask->move(ui.widget->mapToGlobal(m_vo->widget()->pos()));
	return QWidget::moveEvent(e);
}

void QtLive::paintEvent(QPaintEvent * e)
{
	return QWidget::paintEvent(e);
}

bool QtLive::eventFilter(QObject * obj, QEvent * e)
{
	/*if (obj == m_vo->widget() && e->type() == QEvent::Paint)
	{
		pMask->resize(m_vo->widget()->geometry().width(), m_vo->widget()->geometry().height());
		pMask->move(ui.widget->mapToGlobal(m_vo->widget()->pos()));
	}*/

	return QWidget::eventFilter(obj, e);
}
