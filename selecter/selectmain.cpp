/*************************************************************************
	> File Name: selectmain.cpp
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/
#include "selecter.h"
using namespace std;
int main()
{
    selecter *sys = new selecter();
    while(1)
    {
        sys->select();
    }
    return 0;
}
