 /*************************************************************************
	> File Name: tcpClient.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/
#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//tcp客户端
class tcpClient
{
public:
    /*使用connect函数在请求服务的进程套接字（客户端）和提供服务的进程套接字（服务器）建立连接
     */
    int Connect(const string &ip,const unsigned short port);

    int getConnectFd();

    string getIp();
   
    unsigned short int getPort();

    /*
     *发送数据
     */
    int Send(const string &massage);


    /*
     * 接收收据
     * 成功返回数据的字节长度；返回0，
     * 无数据或对等方已经按序结束；出错，返回-1
     */
    int Recv(string &str);

private:
    int _connectFd;
    string _ip;
    unsigned short int _port;
};
#endif
