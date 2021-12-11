#include "trem.h"
#include <QtCore>
#include <QMutex>

static QMutex mutex[7];


Trem::Trem (int ID, int x, int y, int coordXsup, int coordYinf, int * mutexLocked){
    this->ID = ID;
    this->x = x + 20;
    this->y = y;

    this->mutexLocked = mutexLocked;

    this->xSuperior = coordXsup;
    this->xAux = x;

    this->yInferior = coordYinf;
    this->ySuperior = y;

    this->velocidadeConst = 200;
    this->velocidade = 100;
    this->para = 0;
    this->velocidadeAnterior = 0;  
    
    this->mutexList = mutex;
}

void Trem::moverTrem() {
    if(this->para) {
        return;
    }

    if(y == ySuperior && x < xSuperior)
        x+=10;
    else if(x == xSuperior && y < yInferior)
        y+=10;
    else if(y == yInferior && x > xAux)
        x-=10;
    else
        y-=10;

    emit updateGUI(ID, x,y);    //Emite um sinal
    msleep(this->velocidade);
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        this->moverTrem();
        switch (this->ID) {
            case 1:
                regiaoCritica(0, 470, 10, 470, 130);
                regiaoCritica(1, 380, 130, 220, 130);
                regiaoCritica(2, 490, 110, 340, 130);
                break;
            case 2:
                regiaoCritica(0, 510, 130, 510, 10);
                regiaoCritica(3, 650, 130, 490, 110);
                regiaoCritica(4, 760, 110, 610, 130);
                break;
            case 3:
                regiaoCritica(1, 200, 130, 360, 150);
                regiaoCritica(5, 340, 130, 340, 250);
                break;
            case 4:
                regiaoCritica(2, 360, 150, 510, 130);
                regiaoCritica(3, 470, 130, 630, 150);
                regiaoCritica(5, 380, 250, 380, 130);
                regiaoCritica(6, 610, 130, 610, 250);
                break;
            case 5:
                regiaoCritica(4, 630, 150, 780, 130);
                regiaoCritica(6, 650, 250, 650, 130);
                break;
            default:
                break;
        }


    }
}

int Trem::getPara() {
    return this->para;
}

void Trem::setPara(int n) {
    this->para = n;
}


void Trem::regiaoCritica(int trilho, int xInicio, int yInicio, int xFim, int yFim) {
    if(x == xInicio && y == yInicio) {
        if(trilho == 4 && this->ID == 2) {
             qDebug() << "Lock " << this->ID << "\n";
        }
        this->mutexList[trilho].lock();
    } else if (x == xFim && y >= yFim) {
        if(trilho == 4 && this->ID == 2) {
             qDebug() << "unlock " << this->ID << "\n";
        }
        this->mutexList[trilho].unlock();
        this->mutexLocked[trilho] = 0;
    }
}

int Trem::getVelocidade() {
    return this->velocidade;
}

void Trem::setVelocidade(int v) {
    if(this->velocidadeAnterior >= v) {
        this->velocidade = this->velocidadeConst + v;
    } else {
        this->velocidade = this->velocidadeConst - v;
    }
    // this->velocidade = this->velocidadeConst - v;
    this->para = this->velocidade == 200;
    // qDebug() << "atual: , " << v << "anterior: "<< this->velocidadeConst << "\n";
    // qDebug() << this->velocidade << "\n";
    this->velocidadeAnterior = v;
    // emit updateGUI(ID, x,y);    //Emite um sinal
}
