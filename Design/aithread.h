//
// Created by BeiDAmenLinyu on 2024/12/12.
//

#ifndef GOBANG_AITHREAD_H
#define GOBANG_AITHREAD_H

#include "gobang.h"
#include <QObject>
#include <QThread>
#include <ctime>

extern double runningTime;

class AIThread : public QThread {
Q_OBJECT

public:
    explicit AIThread(QObject *parent = nullptr);

signals:
    void AIEnd();

protected:
    void run() override;
};

#endif //GOBANG_AITHREAD_H
