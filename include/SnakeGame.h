#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <QTimer>
#include <QRandomGenerator>

// 贪吃蛇游戏逻辑类
class SnakeGame : public QObject
{
    Q_OBJECT

public:
    explicit SnakeGame(QObject *parent = nullptr);
    ~SnakeGame();

    // 游戏配置常量
    static constexpr int DEFAULT_BOARD_WIDTH = 20;
    static constexpr int DEFAULT_BOARD_HEIGHT = 20;
    static constexpr int DEFAULT_GAME_SPEED = 150; // 毫秒
    static constexpr int POINTS_PER_FOOD = 10;

    // 方向枚举
    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    // 游戏状态枚举
    enum GameState {
        Ready,      // 准备开始
        Playing,    // 正在进行
        Paused,     // 暂停
        GameOver    // 游戏结束
    };

    // 获取蛇的位置列表
    QVector<QPoint> getSnake() const { return snake; }

    // 获取食物位置
    QPoint getFood() const { return food; }

    // 获取当前方向
    Direction getDirection() const { return currentDirection; }

    // 获取游戏状态
    GameState getState() const { return currentState; }

    // 获取分数
    int getScore() const { return score; }

    // 设置游戏区域大小
    void setBoardSize(int width, int height);

    // 获取游戏区域大小
    int getBoardWidth() const { return boardWidth; }
    int getBoardHeight() const { return boardHeight; }

public slots:
    // 开始游戏
    void startGame();

    // 暂停/继续游戏
    void pauseResume();

    // 改变方向
    void changeDirection(Direction dir);

    // 移动蛇
    void move();

signals:
    // 游戏更新信号
    void gameUpdated();

    // 游戏结束信号
    void gameOver();

    // 分数变化信号
    void scoreChanged(int newScore);

private:
    void generateFood();
    bool isCollision() const;
    bool isValidPosition(const QPoint &pos) const;

    QVector<QPoint> snake;          // 蛇的身体位置
    QPoint food;                    // 食物位置
    Direction currentDirection;     // 当前移动方向
    GameState currentState;         // 当前游戏状态
    QTimer *gameTimer;              // 游戏定时器
    int boardWidth;                 // 游戏区域宽度
    int boardHeight;                // 游戏区域高度
    int score;                      // 得分
};

#endif // SNAKEGAME_H