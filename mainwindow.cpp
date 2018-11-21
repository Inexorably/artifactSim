#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "artifactGame.h"

/*******************************/
//Globals for debugging///////////////////////////////////////
/*******************************/
artifactGame testGame;
/*******************************/
/*******************************/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Don't need to press.
    on_testButton_clicked();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_testButton_clicked(){
    ui->testButton->setEnabled(false);
    //qDebug() << "Number of players: " << QString::number(testGame.players.size());
    testGame.createDebugDecks();
    qDebug() << "\t" << QString::number(testGame.players[0].deck.size());
    testGame.gameStart();
    testGame.executeRound();

    on_debugViewGameStateButton_clicked();
    ui->testButton->setEnabled(true);

}

void MainWindow::on_debugViewGameStateButton_clicked(){
    ui->debugViewGameStateButton->setEnabled(0);
    QString tempQString;
    for (size_t i = 0; i < testGame.players.size(); ++i){
        tempQString = "Player " + QString::number(i);
        ui->debugTextBrowser->append(tempQString);
        //Hand.
        ui->debugTextBrowser->append("\tHand:");
        for (size_t j = 0; j < testGame.players[i].hand.size(); ++j){
            tempQString = "\t\t" + QString::number(j) + ": " + testGame.players[i].hand[j].getCurrentName();
            ui->debugTextBrowser->append(tempQString);
        }
        //Deck.
        ui->debugTextBrowser->append("\tDeck:");
        for (size_t j = 0; j < testGame.players[i].deck.size(); ++j){
            tempQString = "\t\t" + QString::number(j) + ": " + testGame.players[i].deck[j].getCurrentName();
            ui->debugTextBrowser->append(tempQString);
        }
        //Lanes.
        for (size_t laneNum = 0; laneNum < testGame.players[i].lanes.size(); ++laneNum){
            tempQString = "\tLane " + QString::number(laneNum);
            ui->debugTextBrowser->append(tempQString);
            ui->debugTextBrowser->append("\t\tCards:");
            for (size_t j = 0; j < testGame.players[i].lanes[laneNum].cards.size(); ++j){
                tempQString = "\t\t" + QString::number(j) + ": " + testGame.players[i].lanes[laneNum].cards[j].getCurrentName();
                ui->debugTextBrowser->append(tempQString);
            }
            ui->debugTextBrowser->append("\t\tImprovements:");
            for (size_t j = 0; j < testGame.players[i].lanes[laneNum].improvements.size(); ++j){
                tempQString = "\t\t" + QString::number(j) + ": " + testGame.players[i].lanes[laneNum].improvements[j].getCurrentName();
                ui->debugTextBrowser->append(tempQString);
            }
        }
        //Graveyard.
        ui->debugTextBrowser->append("\tGraveyard:");
        for (size_t j = 0; j < testGame.players[i].graveyard.size(); ++j){
            tempQString = "\t\t" + QString::number(j) + ": " + testGame.players[i].graveyard[j].getCurrentName();
            ui->debugTextBrowser->append(tempQString);
        }
    }
    ui->debugViewGameStateButton->setEnabled(1);
}
