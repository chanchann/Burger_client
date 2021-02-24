/**
 * g++ xxx.cc -o test -lncurses
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