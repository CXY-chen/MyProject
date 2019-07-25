/*************************************************************************
	> File Name: controller.cpp
	 > Author: 陈玺印 
	 > Mail: 1278500458@qq.com 
 ************************************************************************/
#include "controller.h"
using namespace std;
controller*controller::_control = NULL;
controller*controller::getController()
{
    if(_control == NULL)
    {
        if(_control == NULL)
        {
            _control = new controller();
        }
    }
    return _control;
}
controller::controller()
{
    
    _function = new map<int,view*>();
    _function->insert(map<int, view*>::value_type(REGISTER,new viewRegister));
    _function->insert(map<int, view*>::value_type(LOGIN,new viewLogin));
    _function->insert(map<int, view*>::value_type(INSERT,new viewInsert));
    _function->insert(map<int, view*>::value_type(DELETE, new viewDelete));
    _function->insert(map<int, view*>::value_type(UPDATE, new viewUpdate));
    _function->insert(map<int, view*>::value_type(SELECT, new viewFind));
}

void controller::process(int cliFd,const string &data)
{
    cout <<"控制台做初步解析，将数据传至正确的view视图中"<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr<<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt(); 
    getView(type)->view_handle(cliFd,data);
}

view *controller::getView(int type)
{
    cout <<"选择视图"<<endl;
    map<int, view*>::iterator iter;
    iter = _function->find(type);
    if (iter != _function->end())
    {
        return iter->second;
    }
    else
    {
        cout <<"don't find:"<<type<<endl;
        
    }
}
