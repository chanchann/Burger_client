#ifndef CONTROL_H
#define CONTROL_H
#include <ncurses.h>
#include "../List/List.h"

class Control {//组件基类
public:
	Control(WINDOW *pFather,int height,int width,int starty,int startx,int contype);
	virtual ~Control();
	virtual void show() = 0;//纯虚函数，多态显示不同的控件
	virtual void KeyListen(int &key);//控件键盘监听的多态
	virtual void GetFocus();//控件焦点停留的多态
	WINDOW* GetHandle();//获得控件指针
	int GetType();
	char *Getdata();
protected:
	WINDOW *pCon;//控件指针
	int height;//控件的高度
	int width;//控件的宽度
    int starty;//起始行坐标
	int startx;//起始列坐标
	char *data;//控件的内容
	int contype;// 控件的类型  1-标签、2-编辑框、3-按钮、4-表格、5-提示框、6-下拉框
    WINDOW *pFather;//父窗口指针

};

class Form:public Control//窗口类
{
public:
    Form(int height,int width,int starty,int startx,int contype);
    ~Form();
    void show();
    void KeyListen(int &key);
	bool flag;   //退出keylisten的标志 
protected:
    pList pfirst;// 控件链表或者作为菜单界面的一级菜单链表
	WINDOW *pShadow;	 
};


#endif // CONTROL_H