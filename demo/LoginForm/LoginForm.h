#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "../Control/Control.h"

class LoginForm:public Form
{
public:
    LoginForm(int height,int width,int starty,int startx,int contype);
	char *pName;
	char *pWd;
	char role_id[10];// 登录用户的角色ID
};



#endif // LOGINFORM_H