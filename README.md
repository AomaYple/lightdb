## 介绍

本项目是一个基于C++的的跨平台轻量级键值存储数据库

## 依赖

- 编译
    - [CMake](https://cmake.org) >= 3.30
    - [Ninja](https://ninja-build.org) >= 1.8.2
    - [mimalloc](https://github.com/microsoft/mimalloc) >= 1.0.0
- 运行
    - [mimalloc](https://github.com/microsoft/mimalloc) >= 1.0.0

## 构建

```shell
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release --install-prefix=your_absolute_path
cd build
ninja
```

额外CMake选项

- `-DNATIVE=ON` 启用本机指令集（构建类型为`Release`和编译器为`GCC`或`Clang`时生效）

## 安装

```shell
ninja install
```

## 导入

```cmake
find_package(coContext REQUIRED)
target_link_libraries(your_target
        PRIVATE
        lightdb
)
```
