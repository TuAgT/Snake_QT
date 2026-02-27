#include <QApplication>
#include <GameWindow.h>
#include <Logger.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    // 初始化日志系统
    Logger::getInstance().setLogLevel(LogLevel::DEBUG);
    Logger::getInstance().info("应用程序启动");
    
    // 创建主窗口
    GameWindow window;
    window.show();
    
    int result = QApplication::exec();
    
    Logger::getInstance().info("应用程序退出");
    return result;
}