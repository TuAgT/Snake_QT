# Qt贪吃蛇游戏项目开发与构建文档

## 项目概述

本项目是一个基于Qt框架开发的贪吃蛇游戏，使用C++语言编写。项目采用现代化的CMake构建系统，支持跨平台编译和部署。游戏实现了经典的贪吃蛇玩法，包括蛇的移动控制、食物生成、碰撞检测、得分统计等功能。

## 项目架构

### 目录结构

```
QTGuiDemo/
├── CMakeLists.txt              # CMake构建配置文件
├── README.md                   # 项目说明文档
├── build.sh                    # 构建脚本
├── .gitignore                  # Git忽略文件配置
├── .github/                    # GitHub配置目录
│   └── workflows/              # GitHub Actions工作流
│       ├── build.yml           # 构建工作流
│       └── release.yml         # 发布工作流
├── src/                        # 源代码目录
│   ├── main.cpp                # 应用程序入口点
│   ├── SnakeGame.cpp           # 游戏逻辑实现
│   ├── SnakeWidget.cpp         # 游戏界面实现
│   └── GameWindow.cpp          # 主窗口实现
├── include/                    # 头文件目录
│   ├── SnakeGame.h             # 游戏逻辑声明
│   ├── SnakeWidget.h           # 游戏界面声明
│   └── GameWindow.h            # 主窗口声明
├── docs/                       # 文档目录
│   └── project_structure.md    # 项目结构说明
└── LICENSE                     # 许可证文件
```

### 设计模式

项目采用MVC（Model-View-Controller）架构模式：

- **Model (SnakeGame)**: 处理游戏数据和业务逻辑
  - 蛇的移动逻辑
  - 食物生成算法
  - 碰撞检测机制
  - 得分计算规则

- **View (SnakeWidget)**: 负责界面展示和用户交互
  - 游戏画面渲染
  - 用户输入响应
  - 界面状态更新

- **Controller (GameWindow)**: 协调模型和视图，处理用户操作
  - 主窗口管理
  - 菜单系统
  - 状态显示

## 开发逻辑

### 核心组件

#### SnakeGame类
- **功能**: 游戏核心逻辑处理
- **主要职责**:
  - 管理蛇的位置和方向
  - 处理移动逻辑
  - 检测碰撞（边界、自身）
  - 生成食物位置
  - 计算得分

- **关键技术**:
  - Qt定时器实现游戏循环
  - QVector存储蛇身坐标
  - 信号槽机制通知状态变更

#### SnakeWidget类
- **功能**: 游戏界面渲染
- **主要职责**:
  - 绘制游戏元素（蛇、食物）
  - 处理键盘输入
  - 显示游戏状态
  - 响应用户操作

- **关键技术**:
  - QPainter进行图形绘制
  - 事件处理机制
  - 自定义绘画事件

#### GameWindow类
- **功能**: 主窗口管理
- **主要职责**:
  - 创建主窗口界面
  - 管理菜单系统
  - 显示分数和状态
  - 处理游戏控制

### 游戏机制

#### 移动逻辑
- 蛇按照设定方向持续移动
- 每次移动时头部向前一格，尾部减少一格
- 吃到食物时尾部不减少，实现增长

#### 碰撞检测
- 边界碰撞：检测蛇头是否超出游戏区域
- 自身碰撞：检测蛇头是否碰到身体任意部位

#### 食物生成
- 随机生成不在蛇身体上的位置
- 确保食物位置有效性

## 构建逻辑

### 构建系统配置

#### CMakeLists.txt 配置
```cmake
cmake_minimum_required(VERSION 3.16)  # 兼容Qt6和现代C++特性
project(QTGuiDemo)

set(CMAKE_CXX_STANDARD 20)            # 使用C++20标准
set(CMAKE_AUTOMOC ON)                 # 自动MOC处理
set(CMAKE_AUTORCC ON)                 # 自动RCC处理
set(CMAKE_AUTOUIC ON)                 # 自动UIC处理

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)  # 查找Qt6组件

# 源文件和头文件定义
set(SOURCES ...)
set(HEADERS ...)

# 创建可执行文件并链接库
add_executable(QTGuiDemo ${SOURCES} ${HEADERS})
target_link_libraries(QTGuiDemo Qt::Core Qt::Gui Qt::Widgets)
```

### 构建流程

#### 本地构建
1. **准备工作**:
   ```bash
   mkdir build
   cd build
   ```

2. **配置项目**:
   ```bash
   cmake ..
   ```

3. **编译项目**:
   ```bash
   make
   ```

4. **运行程序**:
   ```bash
   ./QTGuiDemo
   ```

#### 自动化构建 (GitHub Actions)
- **build.yml**: 监听main分支和PR，自动在多平台构建
- **release.yml**: 监听版本标签，自动创建发布版本

### 依赖管理

#### 编译依赖
- Qt6框架 (Core, Gui, Widgets模块)
- C++20编译器支持
- CMake 3.16+

#### 运行时依赖
- Qt6运行时库
- 操作系统图形支持

## 运行逻辑

### 启动流程
1. 应用程序初始化
2. 创建主窗口(GameWindow)
3. 初始化游戏逻辑(SnakeGame)
4. 创建游戏界面(SnakeWidget)
5. 设置游戏参数并开始游戏

### 游戏循环
1. **输入处理**: 响应键盘事件改变蛇的方向
2. **逻辑更新**: 定时器触发移动逻辑
3. **碰撞检测**: 检查各种碰撞情况
4. **界面刷新**: 重新绘制游戏画面
5. **状态更新**: 更新分数和游戏状态

### 控制方式
- **方向键/WASD**: 控制蛇的移动方向
- **空格键**: 暂停/继续游戏
- **R键**: 重新开始游戏
- **菜单快捷键**: Ctrl+N(新游戏), Ctrl+P(暂停), Ctrl+Q(退出)

## CI/CD 流程

### 自动构建
- 监听main分支的推送和Pull Request
- 在Ubuntu、Windows、macOS上自动构建
- 生成构建产物供下载测试

### 自动发布
- 监听版本标签(v*.*.*)的推送
- 自动创建GitHub Release
- 在多平台构建并上传可执行文件
- 生成版本说明文档

## 项目维护

### 代码规范
- 使用Qt信号槽机制进行组件通信
- 遵循RAII原则进行资源管理
- 采用现代C++特性提升代码质量
- 统一的代码风格和注释规范

### 扩展性设计
- 模块化架构便于功能扩展
- 配置常量化便于参数调整
- 接口抽象便于组件替换

## 故障排除

### 常见构建问题
- **CMake版本错误**: 确保使用3.16以上版本
- **Qt库找不到**: 检查Qt6安装和环境变量
- **信号槽连接错误**: 注意Qt6中的API变化

### 运行时问题
- **界面显示异常**: 检查Qt运行时库
- **性能问题**: 优化绘制频率和逻辑计算
- **内存泄漏**: 确认Qt对象的父子关系设置

---

此文档为项目开发和维护提供了全面的指导，涵盖了从架构设计到构建部署的各个方面，有助于开发者快速理解和参与项目。