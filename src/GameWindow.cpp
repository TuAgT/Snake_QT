#include "../include/GameWindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QLabel>
#include <QApplication>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , game(new SnakeGame(this))
    , gameWidget(new SnakeWidget(this))
    , scoreLabel(new QLabel("分数: 0"))
    , statusLabel(new QLabel("准备"))
{
    setWindowTitle("贪吃蛇游戏");
    resize(650, 700);
    LOG_INFO("游戏主窗口已初始化");

    // 设置游戏对象到游戏界面
    gameWidget->setGame(game);

    // 创建菜单
    createMenus();

    // 创建中央部件
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 添加游戏界面
    layout->addWidget(gameWidget);

    // 添加信息显示行
    QHBoxLayout *infoLayout = new QHBoxLayout();
    scoreLabel->setMinimumWidth(150);
    statusLabel->setMinimumWidth(150);
    infoLayout->addWidget(scoreLabel);
    infoLayout->addWidget(statusLabel);
    infoLayout->addStretch(); // 添加弹性空间
    
    layout->addLayout(infoLayout);

    setCentralWidget(centralWidget);
    LOG_INFO("主窗口已设置");

    // 连接信号槽
    connect(game, &SnakeGame::scoreChanged, [this](int newScore) {
        scoreLabel->setText(QString("分数: %1").arg(newScore));
    });

    connect(game, &SnakeGame::gameUpdated, [this]() {
        // 更新状态显示
        QString statusText;
        switch (game->getState()) {
        case SnakeGame::Ready:
            statusText = "准备";
            break;
        case SnakeGame::Playing:
            statusText = "游戏中";
            break;
        case SnakeGame::Paused:
            statusText = "暂停";
            break;
        case SnakeGame::GameOver:
            statusText = "游戏结束";
            break;
        }
        statusLabel->setText(statusText);
    });

    connect(game, &SnakeGame::gameOver, [this]() {
        statusLabel->setText("游戏结束 - 按R键重新开始");
    });
}

GameWindow::~GameWindow()
{
}

void GameWindow::createMenus()
{
    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // 游戏菜单
    QMenu *gameMenu = menuBar->addMenu("游戏");

    startAction = new QAction("新游戏", this);
    startAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(startAction, &QAction::triggered, this, [this]() { startNewGame(); });
    gameMenu->addAction(startAction);

    pauseAction = new QAction("暂停/继续", this);
    pauseAction->setShortcut(QKeySequence("Ctrl+P"));
    connect(pauseAction, &QAction::triggered, this, [this]() { pauseResumeGame(); });
    gameMenu->addAction(pauseAction);

    quitAction = new QAction("退出", this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, []() {
        QApplication::quit();
    });
    gameMenu->addAction(quitAction);

    // 帮助菜单
    QMenu *helpMenu = menuBar->addMenu("帮助");

    aboutAction = new QAction("关于", this);
    connect(aboutAction, &QAction::triggered, this, &GameWindow::aboutGame);
    helpMenu->addAction(aboutAction);
}

void GameWindow::startNewGame() {
    LOG_INFO("开始新游戏");
    game->startGame();
    statusLabel->setText("游戏中");
}

void GameWindow::pauseResumeGame() {
    LOG_DEBUG("暂停/继续游戏");
    game->pauseResume();
}

void GameWindow::aboutGame()
{
    LOG_INFO("显示关于对话框");
    QMessageBox::about(this, "关于贪吃蛇游戏",
                       "贪吃蛇游戏 v1.0\n\n"
                       "控制方式:\n"
                       "- 方向键或WASD: 控制蛇移动\n"
                       "- 空格键: 暂停/继续\n"
                       "- R键: 重新开始游戏\n\n"
                       "吃红色食物可以增长身体并获得分数!\n"
                       "不要撞墙或撞到自己的身体！");
}