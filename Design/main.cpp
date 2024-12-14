#include "chessboard.h"
#include <QApplication>
#include <Windows.h>

int main(int argc, char *argv[]) {
//    HWND hwnd = GetForegroundWindow();
//    ShowWindow(hwnd, SW_HIDE);
    HWND h = GetConsoleWindow();
    ShowWindow(h, SW_HIDE);
    QApplication a(argc, argv);
    ChessBoard ch;
    ch.show();
    return a.exec();
}