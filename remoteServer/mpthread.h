/*************************************************************************
	> File Name: mpthred.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _MPTHRED_H
#define _MPTHRED_H
#include <iostream>
#include <event.h>
#include <json/json.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include "controller.h"
#include "public.h"
using namespace std;
class pthread
{
public:
    pthread(int socketpair_one);

    void run();
    /*
     *监听1端，0端发来clifd时调用
     */
    static void socketpairCb(int fd,short event,void *arg);
     /*
      *线程函数
      */
    static void *pthRun(void *arg);

    static void cliCb(int fd,short event,void *arg);
private:
    struct event_base *_base;
    map<int,struct event*> *_cliEventMap;
};
#endif
