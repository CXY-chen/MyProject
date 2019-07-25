/*************************************************************************
	> File Name: selecter.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _SELECTER
#define _SELECTER
#include <iostream>
#include <string>
#include <stdlib.h>
#include "tcpClient.h"
class selecter
{
public:
    selecter();
    
    void select();


private:
    tcpClient *_selectClient;
};
#endif

