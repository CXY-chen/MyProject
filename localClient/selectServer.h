/*************************************************************************
  > File Name: selectServer.h
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sat 01 Dec 2018 05:06:52 PM CST
 ************************************************************************/

#ifndef _SELECTSERVER_H
#define _SELECTSERVER_H
#include <iostream>
#include <pthread.h>
#include <event.h>
#include "tcpServer.h"
#include "host.h"
#include "public.h"
class selectServer
{
public:
        selectServer();
        /*
         * 监听套接字的回调函数
         */
        static void listenCb(int fd,short event,void *arg);

        /*
         * 客户端套接字的回调函数
         */
        static void cliCb(int fd,short event,void *arg);

        //启动线程循环监听
        static void *selectThreadRun(void *arg);
        
       //发送给信息采集机
        void sendSelect(int fd,string &str);

private:
        tcpServer *_selectSer;  //分布式信息采集机的服务器
        static event_base *_base; //libevent,监听
        static map<int,struct event*> _eventMap;
};

#endif
