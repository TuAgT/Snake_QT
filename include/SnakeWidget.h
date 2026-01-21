#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include "SnakeGame.h"
#include "Logger.h"

// 贪吃蛇游戏显示界面类
class SnakeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeWidget(QWidget *parent = nullptr);
    ~SnakeWidget();

    // 设置关联的游戏逻辑对象
    void setGame(SnakeGame *game);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onGameUpdated();
    void onGameOver();

private:
    void drawSnake(QPainter &painter);
    void drawFood(QPainter &painter);
    void drawGameInfo(QPainter &painter);

    SnakeGame *game;                // 关联的游戏逻辑对象
    int cellSize;                   // 单元格大小
    bool gameOverShown;             // 是否显示游戏结束信息
};

#endif // SNAKEWIDGET_H