/*************************************************************************
	> File Name: tcpServer.h
	 > Author: 陈玺印 
	 > Mail: 1278500458@qq.com 
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
