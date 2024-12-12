//
// Created by BeiDAmenLinyu on 2024/12/9.
//

#ifndef GOBANG_CHESSBOARD_H
#define GOBANG_CHESSBOARD_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QMouseEvent>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <stack>
#include <utility>
#include "gobang.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChessBoard; }
QT_END_NAMESPACE

class ChessBoard : public QWidget {
Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);

    ~ChessBoard() override;
    void startNewGame();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void drawPiece(int x, int y, QPainter *painter, int r);
signals:
    void human();
    void ai();

public slots:
    void AIMove();
    void HumanMove();
    void regret();

private:
    Ui::ChessBoard *ui;
    QPoint clickedPoint;
    std::stack< std::pair<int, int> > pieces;
    int mousePosX;
    int mousePosY;
    int T;  //
    int board[ROW][COLUMN];
};


#endif //GOBANG_CHESSBOARD_H
