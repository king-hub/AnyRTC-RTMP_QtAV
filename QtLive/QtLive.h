#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLive.h"
#include "RtmpGuester.h"
#include <GLWidgetRenderer2.h>
#include <VideoOutput.h>
#include <QResizeEvent>
#include <QMoveEvent>

#include <QPushButton> 
#include <QPainter>

class MyButton : public QPushButton
{
	Q_OBJECT
public:
	MyButton(const QString &text, QWidget *parent = Q_NULLPTR)
		:QPushButton(text, parent)
	{
		setAutoFillBackground(true);
	}

protected:
	virtual void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.fillRect(this->rect(), QColor(0, 0, 255, 80));
		//return QPushButton::paintEvent(event);
	}
};


class QtLive : public QMainWindow, public RTMPGuesterEvent, public FrameReciver
{
	Q_OBJECT

public:
	QtLive(QWidget *parent = Q_NULLPTR);

public:
	virtual void OnRtmplayerOK() {};
	virtual void OnRtmplayerStatus(int cacheTime, int curBitrate) {};
	virtual void OnRtmplayerCache(int time) {};
	virtual void OnRtmplayerClosed(int errcode) {};

private:
	virtual void OnFrame(FrameRef frame) override;
	Q_INVOKABLE void showFrame(FrameRef frame);
protected:
	void onBtnClicked();
	virtual void resizeEvent(QResizeEvent *e);
	virtual void moveEvent(QMoveEvent *e);
	virtual void paintEvent(QPaintEvent *e);
	virtual bool eventFilter(QObject *obj, QEvent *e);
private:
	Ui::QtLiveClass ui;
	RTMPGuester		*m_pAVRtmplayer;
	
	QtAV::GLWidgetRenderer2 *pRenderW;
	QtAV::VideoOutput *m_vo;
	QWidget *pMask;
};
