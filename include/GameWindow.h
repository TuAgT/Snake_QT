#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include "SnakeGame.h"
#include "SnakeWidget.h"
#include "Logger.h"

// 主游戏窗口类
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void startNewGame();

    void pauseResumeGame() const;

    void pauseResumeGame();
    void aboutGame();

private:
    void createMenus();

    SnakeGame *game;                // 游戏逻辑对象
    SnakeWidget *gameWidget;        // 游戏显示部件
    QLabel *scoreLabel;             // 分数标签
    QLabel *statusLabel;            // 状态标签
    QAction *startAction;           // 开始游戏动作
    QAction *pauseAction;           // 暂停/继续动作
    QAction *quitAction;            // 退出动作
    QAction *aboutAction;           // 关于动作
};

#endif // GAMEWINDOW_H