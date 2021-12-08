#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
//    Trem(int ID, int x, int y, int coordXsup, int coordYinf);  //construtor
    Trem(int ID, int x, int y, int coordXsup, int coordYinf);  //construtor
    void run();         // função a ser executada pela thread
    void setVelocidade(int v);
    int getVelocidade();
    int getPara();
    void setPara(int n);
    void moverTrem();
    void regiaoCritica(int trilho, int xInicio, int yInicio, int xFim, int yFim);
    QMutex * mutexList;


//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:

    int xSuperior;
    int xAux;
    int yInferior;
    int ySuperior;
    int x;
    int y;
    int ID;
    int sleep;
    int velocidadeConst;
    int velocidade;
    bool para;
};

#endif // TREM_H
