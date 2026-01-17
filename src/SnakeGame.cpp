#include "../include/SnakeGame.h"
#include <QDebug>

SnakeGame::SnakeGame(QObject *parent)
    : QObject(parent)
    , currentDirection(Right)
    , currentState(Ready)
    , boardWidth(DEFAULT_BOARD_WIDTH)
    , boardHeight(DEFAULT_BOARD_HEIGHT)
    , score(0)
{
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &SnakeGame::move);
    gameTimer->setInterval(DEFAULT_GAME_SPEED); // 游戏速度
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::setBoardSize(int width, int height)
{
    boardWidth = width;
    boardHeight = height;
}

void SnakeGame::startGame()
{
    // 初始化蛇的位置（在中央）
    snake.clear();
    snake.append(QPoint(boardWidth / 2, boardHeight / 2));
    snake.append(QPoint(boardWidth / 2 - 1, boardHeight / 2));
    snake.append(QPoint(boardWidth / 2 - 2, boardHeight / 2));

    currentDirection = Right;
    score = 0;
    currentState = Playing;
    
    generateFood();
    gameTimer->start();
    
    emit gameUpdated();
    emit scoreChanged(score);
}

void SnakeGame::pauseResume()
{
    if (currentState == Playing) {
        currentState = Paused;
        gameTimer->stop();
    } else if (currentState == Paused) {
        currentState = Playing;
        gameTimer->start();
    }
    
    emit gameUpdated();
}

void SnakeGame::changeDirection(SnakeGame::Direction dir)
{
    // 防止蛇反向移动（比如正在向右移动时不能直接向左）
    if ((currentDirection == Up && dir == Down) ||
        (currentDirection == Down && dir == Up) ||
        (currentDirection == Left && dir == Right) ||
        (currentDirection == Right && dir == Left)) {
        return;
    }
    
    currentDirection = dir;
}

void SnakeGame::move()
{
    if (currentState != Playing) {
        return;
    }

    QPoint head = snake.first();
    QPoint newHead = head;

    // 根据当前方向计算新的头部位置
    switch (currentDirection) {
    case Up:
        newHead.setY(head.y() - 1);
        break;
    case Down:
        newHead.setY(head.y() + 1);
        break;
    case Left:
        newHead.setX(head.x() - 1);
        break;
    case Right:
        newHead.setX(head.x() + 1);
        break;
    }

    // 检查是否撞墙
    if (!isValidPosition(newHead)) {
        currentState = GameOver;
        gameTimer->stop();
        emit gameOver();
        emit gameUpdated();
        return;
    }

    // 检查是否撞到自己
    if (snake.contains(newHead)) {
        currentState = GameOver;
        gameTimer->stop();
        emit gameOver();
        emit gameUpdated();
        return;
    }

    // 将新头部添加到蛇身
    snake.insert(0, newHead);

    // 检查是否吃到食物
    if (newHead == food) {
        // 吃到食物，增加分数
        score += POINTS_PER_FOOD;
        emit scoreChanged(score);
        generateFood(); // 生成新食物
    } else {
        // 没吃到食物，移除尾部
        snake.removeLast();
    }

    emit gameUpdated();
}

void SnakeGame::generateFood()
{
    // 生成不在蛇身体上的随机食物位置
    QPoint newFood;
    do {
        newFood = QPoint(
            QRandomGenerator::global()->bounded(boardWidth),
            QRandomGenerator::global()->bounded(boardHeight)
        );
    } while (snake.contains(newFood));
    
    food = newFood;
}

bool SnakeGame::isCollision() const
{
    QPoint head = snake.first();
    
    // 检查是否撞墙
    if (!isValidPosition(head)) {
        return true;
    }
    
    // 检查是否撞到自己（排除头部本身）
    for (int i = 1; i < snake.size(); ++i) {
        if (head == snake[i]) {
            return true;
        }
    }
    
    return false;
}

bool SnakeGame::isValidPosition(const QPoint &pos) const
{
    return pos.x() >= 0 && pos.x() < boardWidth &&
           pos.y() >= 0 && pos.y() < boardHeight;
}