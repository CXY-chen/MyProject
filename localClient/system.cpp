/*************************************************************************
  > File Name: curcurSystem.cpp
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sun 02 Dec 2018 09:19:41 PM CST
 ************************************************************************/
#include "system.h"
using namespace std;
curSystem::curSystem()
{
    //构造一个当前工作界面
    _worker = new interface();
}
void curSystem::menu()
{
    cout << "**************************************************************" << endl;
    cout << "*                         1 登陆                             *" << endl;
    cout << "*                         2 注册                             *" << endl;
    cout << "*                         3 退出                             *" << endl;
    cout << "**************************************************************" << endl;
}
//注册
void curSystem::Register()
{
    string name;
    cout <<"cin name:"<<endl;
    cin >>name;
    string pw;
    cout <<"cin pw"<<endl;
    cin >>pw;

    //组装json包
    Json::Value val;
    val["fd"] = -1;
    val["type"] = REGISTER;
    val["name"] = name;
    val["pw"] = pw;
    //向服务器发送注册信息
    host::getHost()->sendToHost(val.toStyledString());

    //接收服务器回应
    string recvMessage;
    host::getHost()->recvFromHost(recvMessage);
    cout <<recvMessage<<endl;
    Json::Reader read;
    if(read.parse(recvMessage.c_str(),val) == 0)
    {
        cerr<<"read fail;errno:"<<errno<<endl;
    }
    cout <<"json recv:"<<val.toStyledString();
    cout <<val["massage"]<<endl;
}



void curSystem::Login()
{
    string name;
    cout <<"cin name"<<endl;
    cin >>name;

    string pw;
    cout <<"cin pw"<<endl;
    cin >>pw;

    //组装Json包
    Json::Value val;
    val["type"] = LOGIN;
    val["fd"] = -1;
    val["name"] = name;
    val["pw"] = pw;
    

    //向服务器发送登录消息
    host::getHost()->sendToHost(val.toStyledString());
    cout <<val.toStyledString()<<endl;

    //接收服务器回应
    string recvmessage;
    host::getHost()->recvFromHost(recvmessage);
    cout<<recvmessage<<endl;
    
    
    Json::Reader read;
    if(read.parse(recvmessage.c_str(),val) == 0)
    {
        cerr<<"read fail;errno:"<<errno<<endl;
    }
    cout <<"json recv:"<<val.toStyledString();

    
    string r =val["massage"].toStyledString();

    string s= "\"login success\"\n";

    //如果登录成功跳转到工作界面
    if(r == s)
    {
        cout <<"login success!"<<endl;
        _worker->run();
    }

}
void curSystem::Exit()
{
    /*
     *此处的客户端关闭，直接调用exit退出，此时服务端recv返回0
     */
    cout <<"感谢使用，永别了！"<<endl;
    exit(0);
}
curSystem::~curSystem()
{
    delete _worker;
}

