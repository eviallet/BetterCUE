#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
	
	_k70 = new Keyboard(this);
	onRefreshClicked(); // loading device infos


	connect(ui->btn_refresh, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
	connect(ui->btn_led_random, &QPushButton::clicked, _k70, &Keyboard::ledsRandom);
	connect(ui->btn_led_random, &QPushButton::clicked, this, &MainWindow::onLedsClicked);
}

void MainWindow::onRefreshClicked() {
	ui->label_device->setText(_k70->loadDeviceInfos());
}

void MainWindow::onLedsClicked() {
	QPushButton *btn = (QPushButton*)sender();
	if (btn->text() == btn->accessibleName())
		btn->setText("Stop");
	else
		btn->setText(btn->accessibleName());
}

MainWindow::~MainWindow() {
    delete ui;
}

