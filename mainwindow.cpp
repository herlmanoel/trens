#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <string.h>


QMutex mut;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int mutexLocked[7];

    for (int i = 0; i < 7; i++) {
        mutexLocked[i] = 0;
    }

    // Cria o trem com seu (ID, posição X, posição Y)
    // int ID, int x, int y, int coordXsup, int coordYinf
    trem1 = new Trem(1, 220, 10, 490, 130, mutexLocked);
    trem2 = new Trem(2, 490, 10, 760, 130, mutexLocked);
    trem3 = new Trem(3, 90, 130, 360, 250, mutexLocked);
    // x, y, xS, xS, x, y, yI, yI
    trem4 = new Trem(4, 360, 130, 630, 250, mutexLocked);
    trem5 = new Trem(5, 630, 130, 900, 250, mutexLocked);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();

//    ui->sliderTrem1->setValue(50);
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem3->setGeometry(x,y,21,17);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem4->setGeometry(x,y,21,17);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem5->setGeometry(x,y,21,17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_sliderTrem1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}

void MainWindow::on_sliderTrem2_valueChanged(int value)
{

    trem2->setVelocidade(value);
}

void MainWindow::on_sliderTrem3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}

void MainWindow::on_sliderTrem4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}

void MainWindow::on_sliderTrem5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}
