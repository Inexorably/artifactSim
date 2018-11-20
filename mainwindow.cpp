#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "artifactGame.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_testButton_clicked(){
    //Test default constructor of artifactGame.
    artifactGame testGame;
}
