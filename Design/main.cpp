#include "chessboard.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChessBoard ch;
    ch.show();
    return a.exec();
}