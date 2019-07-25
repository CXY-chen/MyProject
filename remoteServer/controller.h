/*************************************************************************
	> File Name: controller.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include <map>
#include "view.h"
#include "public.h"
class controller
{
    public:
        static controller *getController();
        void process(int cliFd,const string &data);
        view *getView(int type);
    private:
        controller();
        static controller * _control;
        map<int,view *> *_function;
};
#endif
