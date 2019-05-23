#pragma once

#include <QWidget>
#include "ui_GraphicsView.h"
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsView(QWidget *parent = Q_NULLPTR);
	~GraphicsView();
	void *getRenderDevice();

protected:
	void resizeEvent(QResizeEvent *e);

private:
	Ui::GraphicsView ui;
};
