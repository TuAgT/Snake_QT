#!/bin/bash

echo "正在构建贪吃蛇游戏..."

# 创建构建目录（如果不存在）
if [ ! -d "build" ]; then
    mkdir build
fi

# 切换到构建目录
cd build

# 运行cmake
cmake ..

# 构建项目
make

echo "构建完成!"
echo "运行 ./QTGuiDemo 来启动游戏"