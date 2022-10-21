# MiniCRT

迷你C语言运行库（部分C++支持）

《程序员的自我修养》最后一章项目实践
书中的代码还是32位系统的，根据新的环境进行了一些适配

## 环境

- 只支持64位linux系统
- gcc 12.2.0
- ld 2.39.0

## 使用方法
### 直接运行脚本
```
# 编译
source run.sh
# 测试
./test # c
./testpp # cpp
```
### 使用cmake
暂无法使用

## 支持的特性：
- CRT初始化
- 堆的实现：malloc和free
- IO与文件操作：fopen, fread, printf等
- 字符串相关操作：strcpy, strlen等
---
c++部分：
- 构造和析构
- string类
- new和delete

## 适配的内容
- 使用64位汇编代码以及syscall
- 64位调用惯例的参数不全位于栈中，调用gcc內建函数实现printf的可变参数
- c++14 开始delete操作符使用了新的参数
- 将.ctor段改成了.init_array段
