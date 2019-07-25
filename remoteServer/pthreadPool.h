/*************************************************************************
	> File Name: pthreadPool.h
	> Author: 计献之 
	> Mail: 1841531744@qq.com 
	> Created Time: Sat 15 Dec 2018 07:19:34 PM CST
 ************************************************************************/

#ifndef _PTHREADPOOL_H
#define _PTHREADPOOL_H
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <errno.h>
#include <stdlib.h>
#include "mpthread.h"
#include <event.h>
using namespace std;
class pthreadPool
{
    public:
        pthreadPool(int num,struct event_base* base);
        void sendCliFdToPthread(int fd);
        static void recvEventNumFromThread(int fd,short event,void *arg);
      
    private:
        //vecroc<pthread_id> _pid;
        map<int,int>_pthreadEventNumMap;  
};
#endif
