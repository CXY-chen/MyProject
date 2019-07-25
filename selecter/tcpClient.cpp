/*************************************************************************
  > File Name: tcpClient.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/

#include "tcpClient.h"
using namespace std;

/*
 * 使用connect函数在请求服务的进程套接字（客户端）和提供服务的进程套接字（服务器）建立连接
 */
int tcpClient::Connect(const string &ip,const unsigned short port)
{
    this-> _ip = ip;
    this-> _port = port;
    /* 创建一个客户端套接字，AF_INET(IPv4因特网域)，SOCK_STREAM(TCP协议)，protocol为0（表示给定的域和套接字类型选择默认协议）         */
    _connectFd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == _connectFd)
    {
        cerr<<"connectfd create fail;errno:"<<errno<<endl;
        close(_connectFd);
        return -1;
    }
    /*
     * 一个地址标识一个特定通信域的套接字端点，地址格式与这个特定的通信域相关
            IPv4因特网域（AF_INET）中，套接字地址用sockaddr_in表示
     */
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    /*
     *          htons()把unsigned short类型从主机序转换到网络序
     */
    addr.sin_port = htons(_port);
    /*
     *          inet_addr()的功能是将一个点分十进制的IP转换成一个长整数型数（u_long类型）
     *                   */
    addr.sin_addr.s_addr = inet_addr(_ip.c_str());
    /*
     *   套接字描述符处于非阻塞模式时，在不能马上建立连接时，connect将会返回
     *       -1并将errno设置为特殊错误码EINPROGRESS。
     */

    // ！！！连接应该有一定的重连机制，提高网络容错率；poll和select监听


    if(-1 == connect(_connectFd,(struct sockaddr *)&addr,sizeof(addr)))
    {
        cerr<<"connect fail;error:"<<errno<<endl;
        cout <<"_connectFd" <<_connectFd<<"Server connect fail"<<endl;
        exit(0);
    }
    return _connectFd;
}
int tcpClient::getConnectFd()
{
    return _connectFd;
}
string tcpClient::getIp()
{
    return _ip;
}
unsigned short int tcpClient::getPort()
{
    return this->_port;
}
/*
 *      *发送数据
 */
int tcpClient::Send(const string &massage)
{
    /*
     *          *类似write()函数，使用send时套接字必须已经连接。
     *          *成功返回发送的字节数，失败返回-1；
     *          send成功返回并不表示另一端就一定接收了数据，只能保证send成功返回时
     *          数据已经被无错误的发送到网络驱动程序。
     *               对于支持报文边界的协议，如果尝试发送的单个报文长度超过协议支持的最大长度，
     *                   那么send会失败，并将errno设置为EMSGSIZE。对于字节流协议
     *                      send会阻塞直到整个数据传输完成
     */
    int flag = send(_connectFd,massage.c_str(),strlen(massage.c_str()),0);
    return flag;
}

/*
 *      * 接收收据
 *           * 成功返回数据的字节长度；返回0，无数据或对等方已经按序结束；出错，返回-1
 */
int tcpClient::Recv(string &str)
{
    char buff[1024] = {0};
    int flag = recv(_connectFd,buff,1023,0);
    str = buff;
    return flag;
}


