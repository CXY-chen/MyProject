/*************************************************************************
	> File Name: tcpServer.h
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Fri 30 Nov 2018 04:32:07 PM CST
 ************************************************************************/

#ifndef _TCPSERVER_H
#define _TCPSERVER_H
#include <iostream>
#include <string>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
//TCP服务端
class tcpServer
{
public:
    /*
     * 创建监听套接字
     */
    tcpServer(const string &ip,const unsigned short port);
    
    int Accept();
   
    int Send(int fd,const string &str);
   
    int Recv(int fd,string &str);
   
    string getIp();
   
    unsigned short getPort();
   
    int getListenFd();
    
private:
    string _ip;
    unsigned short _port;
    int _listenFd;
};
#endif
