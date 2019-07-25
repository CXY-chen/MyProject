/*************************************************************************
	> File Name: system.h
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Sun 02 Dec 2018 12:57:02 AM CST
 ************************************************************************/

#ifndef _SYSTEM_H
#define _SYSTEM_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <json/json.h>
#include "interface.h"
#include "public.h"
class curSystem
{
public:
    curSystem();
    void menu();
    //注册
    void Register();
    void Login();
    void Exit();
    ~curSystem();
private:
    interface *_worker;
};
#endif
