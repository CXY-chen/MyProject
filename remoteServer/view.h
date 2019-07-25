/*************************************************************************
	> File Name: view.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _VIEW_H
#define _VIEW_H
#include <iostream>
#include <string>
#include <json/json.h>
#include "public.h"
#include "mainServer.h"
#include "database.h"
using namespace std;
class view
{
    public:
        virtual void view_handle(int cliFd,const string &data) = 0;
    
};

class viewInsert:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};

class viewDelete:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};

class viewUpdate:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};


class viewFind:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};
class viewRegister:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};
class viewLogin:public view
{
    public:
        void view_handle(int cliFd,const string &data);
};
#endif
