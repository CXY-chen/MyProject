/*************************************************************************
	> File Name: mainstart.cpp
 > Author: 陈玺印 
 > Mail: 1278500458@qq.com 
 ************************************************************************/
#include "server.h"
using namespace std;
int main()
{
    server *ser = new server();
    ser->run();
   return 0;
}
