/**
 * g++ xxx.cc -o test -lncurses
 * https://blog.csdn.net/Zhanganliu/article/details/79927253
 * 
*/

/*
printw实际上这个消息打印到了一个叫作“stdscr”的虚拟窗口上，没有被直接输出到屏幕上。
printw()函数的作用是不断将一些显示标记和相关的数据结构写在虚拟显示器上，并将这些数据写入
stdscr 的缓冲区内。
为了显示这些缓冲区中的数据我们必须使用refresh（）函数告诉curses系统将缓冲区的内容输出到屏幕上。
*/

#include <ncurses.h>

int main() {
    initscr();    /* 初始化，进入NCURSES 模式*/
    printw("Hello World !!!");   /* 在虚拟屏幕上打印Hello, World!!! */
    refresh();    /* 将虚拟屏幕上的内容写到显示器上，并刷新*/
    getchar();    /* 等待用户输入*/
    endwin();     /* 退出NCURSES 模式*/
    return 0;
}