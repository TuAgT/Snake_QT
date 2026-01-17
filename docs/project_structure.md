# 项目结构说明

## 目录结构

```
QTGuiDemo/
├── CMakeLists.txt          # CMake 构建配置文件
├── README.md               # 项目说明文档
├── build.sh                # 构建脚本
├── .gitignore             # Git 忽略文件配置
├── src/                   # 源代码目录
│   ├── main.cpp           # 应用程序入口点
│   ├── SnakeGame.cpp      # 游戏逻辑实现
│   ├── SnakeWidget.cpp    # 游戏界面实现
│   └── GameWindow.cpp     # 主窗口实现
├── include/               # 头文件目录
│   ├── SnakeGame.h        # 游戏逻辑声明
│   ├── SnakeWidget.h      # 游戏界面声明
│   └── GameWindow.h       # 主窗口声明
└── docs/                  # 文档目录
    └── project_structure.md # 项目结构说明
```

## 文件说明

### src/ 目录
- **main.cpp**: 应用程序的主入口点，创建并显示主窗口
- **SnakeGame.cpp**: 实现游戏核心逻辑，包括蛇的移动、食物生成、碰撞检测和计分
- **SnakeWidget.cpp**: 实现游戏的绘制逻辑和用户输入处理
- **GameWindow.cpp**: 实现主窗口界面，包括菜单、状态栏等

### include/ 目录
- **SnakeGame.h**: 定义 SnakeGame 类接口，包含游戏状态枚举、方向枚举等
- **SnakeWidget.h**: 定义 SnakeWidget 类接口，继承自 QWidget
- **GameWindow.h**: 定义 GameWindow 类接口，继承自 QMainWindow

### docs/ 目录
- **project_structure.md**: 项目结构说明文档

## 设计模式

项目采用 MVC (Model-View-Controller) 架构模式：
- **Model (SnakeGame)**: 处理游戏数据和业务逻辑
- **View (SnakeWidget)**: 负责界面展示和用户交互
- **Controller (GameWindow)**: 协调模型和视图，处理用户操作

## 编译说明

使用 CMake 构建系统，支持跨平台编译。