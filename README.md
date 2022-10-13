# MiniCRT

迷你C语言运行库，来自《程序员的自我修养》
只支持64位linux系统（使用64位汇编）

## 使用方法
### 直接运行脚本
```
source run.sh
./test
```
### 使用cmake
```
mkadir build
cd build
cmake ..
make
./test
```

## 支持的特性：
- CRT初始化
- 堆的实现：malloc和free
- IO与文件操作：fopen, fread等
- 字符串相关操作：strcpy, strlen等
