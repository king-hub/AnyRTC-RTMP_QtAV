#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtD3d9Player.h"

class QtD3d9Player : public QWidget
{
	Q_OBJECT

public:
	QtD3d9Player(QWidget *parent = Q_NULLPTR);



private:
	Ui::QtD3d9PlayerClass ui;
};
