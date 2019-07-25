/*************************************************************************
  > File Name: interface.h
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sat 01 Dec 2018 04:57:01 PM CST
 ************************************************************************/

#ifndef _INTERFACE_H
#define _INTERFACE_H
#include <iostream>
#include <math.h>
#include <json/json.h>
#include <string>
#include "public.h"
#include "selectServer.h"
#include "host.h"

class interface
{
    public:
        interface();
        
        /*
         *线程函数，负责从host接受jscon包，类型为-1时属于本机，否则数据发给信息采集机服务器        */
       static void* recvFromHost(void *arg);
        /*
         *增删查改
         */
        void meun();
        void run();
        void Insert();
        void Delete();
        void Update();
        void Select();
        void Paint_Heart();
        void Paint_Rose();

        void recvFromHost();
      
    private:
        selectServer *_selectSer;  
};
#endif
