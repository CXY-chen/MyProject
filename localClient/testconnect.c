/*************************************************************************
	> File Name: testconnect.cpp
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Sat 12 Jan 2019 11:47:31 AM CST
 ************************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
using namespace std;
int main()
{
    string _ip = "127.0.0.1";
    short _port;
    cin >>_port;
    int _connectFd = socket(AF_INET,SOCK_STREAM,0);
    cout<<"_connectFd;"<<_connectFd<<endl;
    if(-1 == _connectFd)
    {
        cerr<<"connectfd create fail;errno:"<<errno<<endl;
        close(_connectFd);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    /*
     *          htons()把unsigned short类型从主机序转换到网络序
     */
    addr.sin_port = htons(_port);
    
    addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    if(-1 == connect(_connectFd,(struct sockaddr *)&addr,sizeof(addr)))
    {
        cerr<<"connect fail;error:"<<errno<<endl;
        cout <<"_connectFd" <<_connectFd<<"Server connect fail"<<endl;
        exit(0);
    }
    cout <<"success"<<endl;
    return 0;
}
