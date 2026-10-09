# CLion 靠这个文件来编译整个项目。
# 没有它的话，CLion 无法把当前目录识别成 C++ 项目，"运行"按钮会退化成
# 只编译当前打开的那一个 .cpp 文件，链接时就会报一堆 undefined reference。

cmake_minimum_required(VERSION 3.15)

# 项目名（不用中文，避免个别工具链处理中文路径时出问题）
project(ecosystem_simulation CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============ 中文输出编码 ============
# 源文件是 UTF-8，这里也统一让编译器把中文字面量按 UTF-8 写进 exe。
# 控制台那边则由 main.cpp 开头的 SetConsoleOutputCP(CP_UTF8) 负责切到 UTF-8，
# 两边都是 UTF-8，中文就不会乱码，也不需要手动敲 chcp。
if (WIN32)
    if (MSVC)
        add_compile_options(/utf-8)
    else ()
        add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
    endif ()
endif ()

# 本项目全部源文件。
# 注意：以后新增 .cpp 文件，一定要记得加到下面这份清单里，
# 否则 CMake/CLion 不会编译它，链接时又会报 undefined reference。
add_executable(ecosystem
        main.cpp
        Organism.cpp
        Fish.cpp
        bigFish.cpp
        smallFish.cpp
        World.cpp
)