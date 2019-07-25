/*************************************************************************
  > File Name: tcpServer.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/
#include "tcpServer.h"
using namespace std;
/*
 *      * 创建监听套接字
 */
tcpServer::tcpServer(const string &ip,const unsigned short port)
{
    _ip = ip;
    _port = port;
    _listenFd = socket(AF_INET,SOCK_STREAM,0);

    if(-1 == _listenFd)
    {
        cerr<<"ser create fail:errno:"<<errno<<endl;
        return;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    /*
     *          *将套接字与地址关联
     *                   *将客户端套接字关联一个地址没有多少意义，系统可以选择默认的地址
     *                   然而，对于服务器，需要给一个接受客户端请求的服务器套接字关联上一个众所周知的地址。
     */
    if(-1 == bind(_listenFd,(struct sockaddr *)&addr,sizeof(addr)))
    {
        cerr <<"bind fail;errno:" <<errno<<endl;
        return;
    }

    if(-1 == listen(_listenFd,20))
    {
        cerr <<"listen fail;errno:"<<errno<<endl;
        return;
    }
 }   
int tcpServer::Accept()
{
    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    /*
     *
     *服务器调用了listen,所用的套接字就能接收连接请求。使用accept函数获得连接并请求建立连接
     *      accept所返回的文件描述符是套接字描述符，该描述符连接到调用connect的客户端。
     *              这个新的套接字描述符和原始套接字（_listenFd）具有相同的套接字类型和地址族。
     *                  传给accept的原始套接字没有关联到这个连接，而是继续保持可用状态并接受其他连接请求。
     *                                     另外，服务器可以使用poll,select来等待一个请求
     *                                              如果没有连接请求在等待，accept会阻塞直到一个请求到来。
     *                          如果_listenFd处于非阻塞模式，accept会返回-1，并将errno置为EWOUTDBLOCK
     */


    int cli_fd  = accept(_listenFd,(struct sockaddr *)&caddr,&len);
    if(-1 == cli_fd)
    {
        cerr<<"accept fail:errno:"<<errno<<endl;
    }
    return cli_fd;
}
int tcpServer::Send(int fd,const string &str)
{
    int flage = send(fd,str.c_str(),strlen(str.c_str()),0);
    return flage;
}
int tcpServer::Recv(int fd,string &str)
{
    char buff[1024] = {0};

    int flage = recv(fd,buff,1023,0);
    str = buff;
    return flage;
}
string tcpServer::getIp()
{
    return _ip;
}
unsigned short tcpServer::getPort()
{
    return _port;
}
int tcpServer::getListenFd()
{
    return _listenFd;
}

