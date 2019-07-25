/*************************************************************************
	> File Name: sysmain.cpp
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Sun 02 Dec 2018 12:43:09 PM CST
 ************************************************************************/
#include "system.h"
using namespace std;
int main()
{
    //启动系统
    curSystem *Sys = new curSystem();
    while(1)
    {
        //输出用户选择
        Sys->menu();
        int choice;
        cin >>choice;
        switch(choice)
        {
            case 1:
                Sys->Login();
                break;
            case 2:
                Sys->Register();
                break;
            case 3:
                Sys->Exit();
            default:
                cout <<"error input,please try again"<<endl;
                break;
        }
    }
    delete Sys;
    return 0;
}
