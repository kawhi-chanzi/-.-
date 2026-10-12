//
// Created by 铲 on 2026/9/21.
//
#include <iostream>
#include <cstdio>      // fwrite / fflush / stdout
#include <string>      // std::string / std::wstring
#include <streambuf>   // std::streambuf

#include <cstdlib>     // srand 需要它
#include <ctime>       // time 需要它

#ifdef _WIN32
// windows.h 默认会定义 min/max 两个宏，可能和标准库的 std::max 冲突，
// 所以先定义 NOMINMAX 把它关掉（MinGW 的头文件里已经定义过，这里加个保护避免重复定义）
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>   // 下面做转码要用它提供的 Win32 函数
#endif

#include "World.h"

using namespace std;

#ifdef _WIN32
// ============================ 中文乱码适配 ============================
// 问题根源：
//   源码是 UTF-8，编译出来的字符串也是 UTF-8 字节；
//   但 Windows 控制台（cmd / PowerShell）默认按 GBK(936) 代码页显示，
//   而 PowerShell 5.1 还会在启动时把当时的代码页"记死"（[Console]::OutputEncoding），
//   之后程序再怎么改控制台代码页，它那边也不跟着变。
//   => 所以"程序单方面把代码页切成 UTF-8"是没用的，得反过来让程序去迁就控制台。
//
// 做法：
//   把 std::cout 的输出缓冲区换掉。每次要输出时，先看一眼控制台当前用的是哪个代码页：
//   是 UTF-8 就原样写出；是 GBK 之类，就先把 UTF-8 转成对应代码页再写。
// 效果：
//   cmd、PowerShell、CLion 里中文都不会乱码，也不需要手动敲 chcp 65001。
class ConsoleAdaptBuf : public streambuf
{
public:
    ConsoleAdaptBuf()
    {
        // 只读取控制台当前真正在用的输出代码页，不去修改它
        consoleCP = GetConsoleOutputCP();
        // 判断 stdout 是不是真的连着控制台窗口；被重定向到文件/管道时就是 false
        DWORD mode;
        isConsole = GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) != 0;
    }

protected:
    // cout << "一整段字符串" 时，整段走这里
    streamsize xsputn(const char* s, streamsize n) override
    {
        writeAdapted(s, n);
        return n;
    }

    // cout << '单字符' 时走这里（本项目里的单字符都是 ASCII：'.' 'B' 's' 空格 换行）
    int_type overflow(int_type ch) override
    {
        if (ch != traits_type::eof())
        {
            char c = static_cast<char>(ch);
            writeAdapted(&c, 1);
        }
        return ch;
    }

    // cout << endl 会触发 flush，这里顺手把 C 的输入输出缓冲也刷一下，保证输出顺序
    int sync() override
    {
        fflush(stdout);
        return 0;
    }

private:
    UINT consoleCP;   // 控制台当前的输出代码页（936 = GBK，65001 = UTF-8）
    bool isConsole;   // stdout 是否连着控制台

    // 按需要转码后写出
    void writeAdapted(const char* s, streamsize n)
    {
        if (s == nullptr || n <= 0)
        {
            return;
        }

        // 以下两种情况不需要转码：
        //   1) 不是控制台（输出被重定向了）——保持 UTF-8，写文件/管道更通用
        //   2) 控制台本来就是 UTF-8——直接输出即可
        if (!isConsole || consoleCP == CP_UTF8)
        {
            fwrite(s, 1, static_cast<size_t>(n), stdout);
            return;
        }

        // 第一步：UTF-8 -> UTF-16（Windows 内部使用的宽字符）
        int wideLen = MultiByteToWideChar(CP_UTF8, 0, s, static_cast<int>(n), nullptr, 0);
        if (wideLen <= 0)
        {
            fwrite(s, 1, static_cast<size_t>(n), stdout);   // 转换失败就原样写出，至少别丢内容
            return;
        }
        wstring wide(wideLen, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, s, static_cast<int>(n), wide.data(), wideLen);

        // 第二步：UTF-16 -> 控制台代码页（比如 GBK）
        int outLen = WideCharToMultiByte(consoleCP, 0, wide.data(), wideLen, nullptr, 0, nullptr, nullptr);
        if (outLen <= 0)
        {
            fwrite(s, 1, static_cast<size_t>(n), stdout);
            return;
        }
        string out(outLen, '\0');
        WideCharToMultiByte(consoleCP, 0, wide.data(), wideLen, out.data(), outLen, nullptr, nullptr);

        fwrite(out.data(), 1, out.size(), stdout);
    }
};

// 转码缓冲区要一直活到程序结束，所以定义在 main 外面，当作一个全局静态对象
static ConsoleAdaptBuf consoleBuf;
#endif

int main() {
#ifdef _WIN32
    // 换掉 cout 的缓冲区，之后所有中文输出都会自动适配控制台代码页（原理见上面的注释）。
    // 先把原来那个缓冲区记下来，程序结束时要还原回去。
    streambuf* originalBuf = cout.rdbuf(&consoleBuf);
#endif

    // 用当前时间做随机种子，这样每次运行鱼的游动路线都不一样
    srand((unsigned)time(0));

    World world;

    // 往水里放鱼。想加鱼就照这样继续写 addCreature。
    // 大鱼 'B' 是捕食者，小鱼 's' 是猎物。
    world.addCreature(new bigFish(2, 2));
    world.addCreature(new bigFish(17, 8));
    world.addCreature(new smallFish(1, 1));
    world.addCreature(new smallFish(5, 3));
    world.addCreature(new smallFish(8, 4));
    world.addCreature(new smallFish(12, 2));
    world.addCreature(new smallFish(15, 7));

    // 模拟 10 天，每天 World::STEPS_PER_DAY（=3）步。
    // 每一步发生的事件、以及每天结束时的地图和存活数量，
    // 都由 World::step() 内部自动打印，这里不用再管。
    for (int i = 0; i < 10; i++)
    {
        for (int s = 0; s < World::STEPS_PER_DAY; s++)
        {
            world.step();
        }
    }

#ifdef _WIN32
    // 收尾：先把 cout 里还没写完的内容刷出去，再把缓冲区还原成原来的。
    // 这样程序退出时，cout 就不会去访问（可能已经析构的）转码缓冲区，避免出错。
    cout.flush();
    cout.rdbuf(originalBuf);
#endif

    return 0;
}