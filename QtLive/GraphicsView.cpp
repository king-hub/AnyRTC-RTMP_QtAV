#include "GraphicsView.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QVideoWidget>
#include <QTimer>

QGraphicsItem *pItem = nullptr;
QGraphicsProxyWidget *w = nullptr;
QVideoWidget *renderDevice = nullptr;

GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	ui.setupUi(this);
	//setCacheMode(QGraphicsView::CacheBackground);
	QGraphicsScene *pScene = new QGraphicsScene();
	renderDevice = new QVideoWidget();
	w = pScene->addWidget(renderDevice);
	w->resize(1600, 900);
	pItem = dynamic_cast<QGraphicsItem *>(w);
	this->setScene(pScene);
	//QTimer *pTimer = new QTimer();
	//QObject::connect(pTimer, &QTimer::timeout, [this]()
	//{
	//	update();
	//});
}

GraphicsView::~GraphicsView()
{
}

void * GraphicsView::getRenderDevice()
{
	return (void *)renderDevice->winId();
	//return (void *)this->winId();
}

void GraphicsView::resizeEvent(QResizeEvent * e)
{
	fitInView(pItem, Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(e);
}
