#include "../include/SnakeWidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QMessageBox>
#include <QDebug>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent)
    , game(nullptr)
    , cellSize(20)
    , gameOverShown(false)
{
    setFocusPolicy(Qt::StrongFocus); // 允许接收键盘事件
    // 根据默认游戏板大小和单元格大小计算窗口大小
    int defaultWidth = 20 * cellSize + 50;  // 加上边距
    int defaultHeight = 20 * cellSize + 100; // 加上信息显示区域
    setFixedSize(defaultWidth, defaultHeight); // 设置固定大小
    LOG_INFO("SnakeWidget 已初始化");
}

SnakeWidget::~SnakeWidget()
{
}

void SnakeWidget::setGame(SnakeGame *g)
{
    if (game) {
        disconnect(game, &SnakeGame::gameUpdated, this, &SnakeWidget::onGameUpdated);
        disconnect(game, &SnakeGame::gameOver, this, &SnakeWidget::onGameOver);
    }

    game = g;

    if (game) {
        connect(game, &SnakeGame::gameUpdated, this, &SnakeWidget::onGameUpdated);
        connect(game, &SnakeGame::gameOver, this, &SnakeWidget::onGameOver);
        LOG_DEBUG("SnakeWidget 已连接到游戏逻辑");
    }
}

void SnakeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (game) {
        // 绘制网格背景
        painter.fillRect(rect(), Qt::black);

        // 绘制游戏元素
        drawSnake(painter);
        drawFood(painter);
        drawGameInfo(painter);

        // 如果游戏结束，显示游戏结束文本
        if (game->getState() == SnakeGame::GameOver) {
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 24, QFont::Bold));
            painter.drawText(rect(), Qt::AlignCenter, "游戏结束! 按R键重新开始");
        }
    } else {
        // 没有游戏对象时的提示
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 16));
        painter.drawText(rect(), Qt::AlignCenter, "未初始化游戏");
    }

    LOG_DEBUG("绘制游戏界面");
    QWidget::paintEvent(event);
}

void SnakeWidget::drawSnake(QPainter &painter)
{
    if (!game) return;

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green); // 蛇身颜色

    auto snake = game->getSnake();
    for (int i = 0; i < snake.size(); ++i) {
        QPoint pos = snake[i];
        QRect rect(pos.x() * cellSize, pos.y() * cellSize, cellSize, cellSize);
        
        // 蛇头用不同颜色表示
        if (i == 0) {
            painter.setBrush(Qt::darkGreen);
        } else {
            painter.setBrush(Qt::green);
        }
        
        painter.drawRect(rect);
    }
}

void SnakeWidget::drawFood(QPainter &painter)
{
    if (!game) return;

    QPoint foodPos = game->getFood();
    QRect foodRect(foodPos.x() * cellSize, foodPos.y() * cellSize, cellSize, cellSize);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red); // 食物颜色
    painter.drawEllipse(foodRect);
}

void SnakeWidget::drawGameInfo(QPainter &painter)
{
    if (!game) return;

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12));

    // 显示分数
    QString scoreText = QString("分数: %1").arg(game->getScore());
    painter.drawText(10, 20, scoreText);

    // 显示游戏状态
    QString stateText;
    switch (game->getState()) {
    case SnakeGame::Ready:
        stateText = "准备";
        break;
    case SnakeGame::Playing:
        stateText = "游戏中";
        break;
    case SnakeGame::Paused:
        stateText = "暂停";
        break;
    case SnakeGame::GameOver:
        stateText = "游戏结束";
        break;
    }

    painter.drawText(width() - 100, 20, stateText);
}

void SnakeWidget::keyPressEvent(QKeyEvent *event)
{
    if (!game) return;

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        game->changeDirection(SnakeGame::Up);
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        game->changeDirection(SnakeGame::Down);
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        game->changeDirection(SnakeGame::Left);
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        game->changeDirection(SnakeGame::Right);
        break;
    case Qt::Key_Space:
        game->pauseResume();
        break;
    case Qt::Key_R:
        game->startGame();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void SnakeWidget::onGameUpdated()
{
    LOG_DEBUG("界面更新请求");
    update(); // 请求重绘界面
}

void SnakeWidget::onGameOver()
{
    LOG_DEBUG("游戏结束界面更新");
    update(); // 请求重绘界面以显示游戏结束信息
}