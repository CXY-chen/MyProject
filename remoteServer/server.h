/*************************************************************************
	> File Name: server.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <event.h>
#include "pthreadPool.h"
#include "mainServer.h"
#include "database.h"
class server
{
public:
    server();
    void run();
    static void listenCb(int fd,short event,void *arg);

private:
    struct event_base *_base;
    pthreadPool * _pthreadPool;
};
#endif
