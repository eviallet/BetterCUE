#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "Keyboard.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private slots:
	void onRefreshClicked();
	void onLedsClicked();
private:
    Ui::MainWindow *ui;
	Keyboard *_k70;
};

#endif // MAINWINDOW_H
