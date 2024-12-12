//
// Created by BeiDAmenLinyu on 2024/12/12.
//

#include "aithread.h"
double runningTime;

void AIThread::run() {
    clock_t start_time = clock();
    fool();
    clock_t end_time = clock();
    runningTime = (double)(end_time - start_time) / 1000.0;
    emit this->AIEnd();
    QThread::quit();
}

AIThread::AIThread(QObject *parent) : QThread(parent) {

}
