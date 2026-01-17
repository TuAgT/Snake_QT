#include <QApplication>
#include "../include/GameWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    // 创建主窗口
    GameWindow window;
    window.show();
    
    return QApplication::exec();
}