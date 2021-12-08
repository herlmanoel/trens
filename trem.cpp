#include "trem.h"
#include <QtCore>
#include <QMutex>

static QMutex mutex[7];

Trem::Trem (int ID, int x, int y, int coordXsup, int coordYinf){
    this->ID = ID;
    this->x = x + 20;
    this->y = y;

    this->xSuperior = coordXsup;
    this->xAux = x;

    this->yInferior = coordYinf;
    this->ySuperior = y;

    this->velocidadeConst = 200;
    this->velocidade = 100;
    this->para = 0;

    this->mutexList = mutex;
    
}

void Trem::moverTrem() {
    if(y == ySuperior && x < xSuperior)
        x+=10;
    else if(x == xSuperior && y < yInferior)
        y+=10;
    else if(y == yInferior && x > xAux)
        x-=10;
    else
        y-=10;

    emit updateGUI(ID, x,y);    //Emite um sinal
    msleep(velocidade);
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        this->moverTrem();
        
        switch (this->ID) {
            case 1:
                // // this->moverTrem();
                // if(x == 380 && y == 130) {
                //     mutex[1].lock();
                //     // qDebug() << "ENTROU\n";
                // } else if (x == 220 && y >= 130) {
                //     mutex[1].unlock();
                //     // qDebug() << "SAIU\n";
                // }
                regiaoCritica(1, 380, 130, 220, 130);
                // --------------------
                // if(x == 470 && y == 10) {
                //     mutex[0].lock();
                //     // qDebug() << "ENTROU\n";
                // } else if (x == 470 && y == 130) {
                //     mutex[0].unlock();
                //     // qDebug() << "SAIU\n";
                // }
                regiaoCritica(0, 470, 10, 470, 130);
                regiaoCritica(2, 490, 110, 340, 130);
                break;
            case 2:
                // this->moverTrem();
                // if(x == 510 && y == 130) {
                //     mutex[0].lock();
                //     // qDebug() << "ENTROU\n";
                // } else if (x == 510 && y == 10) {
                //     mutex[0].unlock();
                //     // qDebug() << "SAIU\n";
                // }
                regiaoCritica(0, 510, 130, 510, 10);
                break;
            case 3:
                // if(x == 200 && y == 130) {
                //     mutex[1].lock();
                //     // qDebug() << "ENTROU\n";
                // } else if (x == 360 && y == 150) {
                //     mutex[1].unlock();
                //     // qDebug() << "SAIU\n";
                // }
                regiaoCritica(1, 200, 130, 360, 150);
                break;
            case 4:
                // this->moverTrem();
                regiaoCritica(2, 360, 150, 510, 130);
                break;
            case 5:
                // this->moverTrem();

                break;
            default:
                break;
        }


    }
}

void Trem::setVelocidade(int v) {
    this->velocidade = 200 - v;
    this->para = this->velocidade == 200;
    // emit updateGUI(ID, x,y);    //Emite um sinal
}

int Trem::getPara() {
    return this->para;
}

void Trem::setPara(int n) {
    this->para = n;
}


void Trem::regiaoCritica(int trilho, int xInicio, int yInicio, int xFim, int yFim) {
    if(x == xInicio && y == yInicio) {
        this->mutexList[trilho].lock();
        // qDebug() << "ENTROU\n";
    } else if (x == xFim && y >= yFim) {
        this->mutexList[trilho].unlock();
        // qDebug() << "SAIU\n";
    }
}