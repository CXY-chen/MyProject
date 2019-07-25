/*************************************************************************
	> File Name: host.h
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Sat 01 Dec 2018 02:46:50 PM CST
 ************************************************************************/

#ifndef _HOST_H
#define _HOST_H
#include <string>
#include <json/json.h>
#include <errno.h>
#include "tcpClient.h"
class host
{
public:
    static host* getHost(const string &ip = "127.0.0.1",const unsigned short &port = 6000);
    bool changeServer();  //负载均衡
    bool sendToHost(const string &message);
    bool recvFromHost(string &str);
private:
    host(const string &ip,const unsigned short &port);
    static host * _midServer;
    tcpClient *_ser;
    string _balanceIp;
    unsigned short _balancePort;
};
#endif
