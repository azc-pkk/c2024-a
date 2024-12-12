//
// Created by BeiDAmenLinyu on 2024/12/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChessBoard.h" resolved

#include "chessboard.h"
#include "ui_ChessBoard.h"
const int gridCount = 15;
const int gridSize = 40;
const int radius = (double)gridSize / 2 * 0.9;
const int MARGIN = 40;

ChessBoard::ChessBoard(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChessBoard) {

    ui->setupUi(this);
//    ui->messageBox->setWordWrap(true);
    ui->plainTextEdit->setReadOnly(true);
    setMouseTracking(true);
    mousePosX = 0;
    mousePosY = 0;
    setWindowTitle("五子棋");
    aiThread = new AIThread(this);

    connect(this, &ChessBoard::ai, this, &ChessBoard::AIThreadActivate);
    connect(this, &ChessBoard::human, this, &ChessBoard::HumanMove);
    connect(ui->rollbackButton, &QPushButton::clicked, this, &ChessBoard::regret);
    connect(ui->restartButton, &QPushButton::clicked, this, &ChessBoard::reStart);
    connect(aiThread, &AIThread::AIEnd, this, &ChessBoard::AIMove);

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
    QBrush geryBrush(QColor(0, 0, 0, 180));
    QPen pen(Qt::black, 1);
    painter.setPen(pen);

    // 画线
    for (int i = 0; i < gridCount; i++) {
        painter.drawLine(MARGIN, i * gridSize + MARGIN, (gridCount - 1) * gridSize + MARGIN, i * gridSize + MARGIN);
        painter.drawLine(i * gridSize + MARGIN, MARGIN, i * gridSize + MARGIN, (gridCount - 1) * gridSize + MARGIN);
    }
//    painter.drawLine((gridCount - 1) * gridSize + MARGIN * 2, 0, (gridCount - 1) * gridSize + MARGIN * 2, QWidget::height());

    // 画棋子
    for (int i = 0; i < gridCount; i++) {
        for (int j = 0; j < gridCount; j++) {
            if (board[i][j] == 1) {
                painter.setBrush(whiteBrush);
                drawPiece(i, j, &painter, radius);
            }
            else if (board[i][j] == 2) {
                painter.setBrush(blackBrush);
                drawPiece(i, j, &painter, radius);
            }
        }
    }

    if (T % 2 == 0 && board[mousePosX][mousePosY] == 0) {
        painter.setBrush(geryBrush);
        drawPiece(mousePosX, mousePosY, &painter, radius);
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::LeftButton) {
        if (event->pos().x() < MARGIN || event->pos().y() < MARGIN || event->pos().x() > (gridCount - 1) * gridSize + MARGIN || event->pos().y() > (gridCount - 1) * gridSize + MARGIN) {

        }
        else if (T % 2 == 0) {
            clickedPoint = event->pos();
            emit this->human();
        }
    }
}

void ChessBoard::mouseMoveEvent(QMouseEvent *event) {
    if (event->pos().x() < MARGIN || event->pos().y() < MARGIN || event->pos().x() > (gridCount - 1) * gridSize + MARGIN || event->pos().y() > (gridCount - 1) * gridSize + MARGIN) {

    }
    else {
        int x = round(((double) event->pos().x() - MARGIN) / gridSize);
        int y = round(((double) event->pos().y() - MARGIN) / gridSize);
        mousePosX = x;
        mousePosY = y;
        repaint();
    }
}

void ChessBoard::AIThreadActivate() {
    ui->plainTextEdit->appendPlainText("AI 正在思考...");
    aiThread->start();
}

void ChessBoard::AIMove() {
    std::pair<int, int> piece = next_step;
    pieces.push(piece);
    list3.insert(piece);
    list1.insert(piece);
    board[piece.first][piece.second] = 1;
    ui->plainTextEdit->appendPlainText(QString("AI 花了 ") + QString::number(runningTime) + QString(" 秒来思考对策。"));
//    ui->plainTextEdit->appendPlainText(QString::number(runningTime));
//    ui->plainTextEdit->appendPlainText(" 秒来思考对策。");
    repaint();
    T++;
}

void ChessBoard::HumanMove() {
    int x = round((double)(clickedPoint.x() - MARGIN) / gridSize);
    int y = round((double)(clickedPoint.y() - MARGIN) / gridSize);
    pieces.push(std::make_pair(x, y));
    list3.insert(std::make_pair(x, y));
    list2.insert(std::make_pair(x, y));
    board[x][y] = 2;
    T++;
    repaint();
    emit this->ai();
}

void ChessBoard::regret() {
    if (aiThread->isRunning()) {
//        ui->messageBox->setText("AI 正在思考，悔棋失败！");
    ui->plainTextEdit->appendPlainText("AI 正在思考，悔棋失败！");
    }
    else if (!pieces.empty()) {
        std::pair<int, int> piece = pieces.top();
        pieces.pop();
        list1.erase(piece);
        list3.erase(piece);
        board[piece.first][piece.second] = 0;

        piece = pieces.top();
        pieces.pop();
        list2.erase(piece);
        list3.erase(piece);
        board[piece.first][piece.second] = 0;

        ui->plainTextEdit->appendPlainText("悔棋成功！");
        repaint();
    }
    else {
        ui->plainTextEdit->appendPlainText("你还没有下棋！");
    }
}

void ChessBoard::reStart() {
    if (aiThread->isRunning()) {
        ui->plainTextEdit->appendPlainText("AI 正在思考，无法重新开始！");
    }
    else {
        std::pair<int, int> piece;
        while (!pieces.empty()) {
            piece = pieces.top();
            pieces.pop();
            list1.erase(piece);
            list3.erase(piece);

            piece = pieces.top();
            pieces.pop();
            list2.erase(piece);
            list3.erase(piece);
        }
        startNewGame();
        repaint();
        ui->plainTextEdit->setPlainText("重新开始！");
    }
}

void ChessBoard::drawPiece(int x, int y, QPainter *painter, int r) {
    painter->drawEllipse(x * gridSize + MARGIN - r, y * gridSize + MARGIN - r, 2 * r, 2 * r);
}

ChessBoard::~ChessBoard() {
    delete ui;
}
