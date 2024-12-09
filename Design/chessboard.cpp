//
// Created by BeiDAmenLinyu on 2024/12/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChessBoard.h" resolved

#include "chessboard.h"
#include "ui_ChessBoard.h"
const int gridCount = 15;
const int gridSize = 40;
const int radius = (double)gridSize / 2 * 0.9;

ChessBoard::ChessBoard(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChessBoard) {
    ui->setupUi(this);
    this->resize(gridSize * (gridCount - 1), gridSize * (gridCount - 1));
    connect(this, &ChessBoard::ai, this, &ChessBoard::AIMove);
    connect(this, &ChessBoard::human, this, &ChessBoard::HumanMove);
    startNewGame();
}

void ChessBoard::startNewGame() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            board[i][j] = 0;
        }
    }
}

void ChessBoard::paintEvent(QPaintEvent *event) {
    // 绘制背景色
    QPainter painter(this);
    painter.fillRect(rect(), QColor("#de9621"));
    // 设置反锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QPen pen(Qt::black, 1);
    painter.setPen(pen);

    // 画线
    for (int i = 0; i < gridCount; i++) {
        painter.drawLine(0, i * gridSize, QWidget::width(), i * gridSize);
        painter.drawLine(i * gridSize, 0, i * gridSize, QWidget::height());
    }

    // 画棋子
    for (int i = 0; i < gridCount; i++) {
        for (int j = 0; j < gridCount; j++) {
            if (board[i][j] == 1) {
                painter.setBrush(whiteBrush);
                painter.drawEllipse(i * gridSize - radius, j * gridSize - radius, 2 * radius, 2 * radius);
            }
            else if (board[i][j] == 2) {
                painter.setBrush(blackBrush);
                painter.drawEllipse(i * gridSize - radius, j * gridSize - radius, 2 * radius, 2 * radius);
            }
        }
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        if (T % 2 == 0) {
            clickedPoint = event->pos();
            emit this->human();
        }
    }
}

void ChessBoard::AIMove() {
    printf("AI Acting:\n");
    clock_t start_time = clock();
    std::pair<int, int> piece = fool();
    clock_t end_time = clock();
    printf("It takes %lfs for AI to think.\n", (double)(end_time - start_time) / 1000.0);
    list3.insert(piece);
    list1.insert(piece);
    board[piece.first][piece.second] = 1;
    repaint();
    T++;
}

void ChessBoard::HumanMove() {
    int x = round((double)clickedPoint.x() / gridSize);
    int y = round((double)clickedPoint.y() / gridSize);
    list3.insert(std::make_pair(x, y));
    list2.insert(std::make_pair(x, y));
    board[x][y] = 2;
    T++;
    repaint();
    emit this->ai();
}

ChessBoard::~ChessBoard() {
    delete ui;
}
