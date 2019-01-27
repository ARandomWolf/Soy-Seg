#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtGuiApplication1.h"
#include <QtGui>
#include <qpixmap.h>

class QtGuiApplication1 : public QWidget
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	

private slots:
	void on_loadImg_clicked();
	void on_chooseImg_clicked();
	void on_processButton_clicked();

private:
	QString fileName = NULL;
	Ui::QtGuiApplication1Class ui;
};
