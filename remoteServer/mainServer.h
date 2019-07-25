/*************************************************************************
	> File Name: mainServer.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _MAINSERVER_H
#define _MAINSERVER_H
#include "tcpServer.h"
#include "tcpClient.h"
#include <json/json.h>
#include <string>
using namespace std;
class remoteServer
{
    public:
        static remoteServer *getServer();
        int Recv(int fd,string &str);
        int Send(int fd,const string &str);
        int Accept();
        int getListenFd();
    private:
        /*
         *构造私有化
         */
        remoteServer(const string &ip,short port);
        /*
         * 最大可开的服务器数量
         */
        static remoteServer *_mainServer;
        tcpServer *_server;
        tcpClient *_client;
};
#endif
