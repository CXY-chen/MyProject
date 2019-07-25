/*************************************************************************
  > File Name: host.cpp
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sun 02 Dec 2018 08:25:02 PM CST
 ************************************************************************/

#include "host.h"
using namespace std;

host*host::_midServer = NULL;

host::host(const string &ip,const unsigned short &port)
{
    _balanceIp = ip;
    _balancePort = port;
    _ser = new tcpClient();
    _ser->Connect(_balanceIp,_balancePort);
    
    string str;
    _ser->Recv(str);

    Json ::Value val;
    Json ::Reader read;

    if(-1 == read.parse(str.c_str(),val))
    {
        cerr<<"read json fail;errno:"<<endl;
        return;
    }
    string ipnew = val["ip"].asString();
    short portnew = val["port"].asInt();
    cout <<"newip:"<<ipnew<<"newport"<<portnew<<endl;
    close(_ser->getConnectFd());

    sleep(10);
    _ser->Connect(ipnew,portnew);
    
}

host* host::getHost(const string &ip,const unsigned short &port)
{
    if(NULL == _midServer)
    {
        if(NULL == _midServer)
        {
            cout <<"balance server ip = 127.0.0.1"<<endl;
            cout <<"input balance server port:"<<endl;
            short port;
            cin >>port;
            string i = "127.0.0.1";;
            _midServer = new host(i,port);
            
        }
    }
    return _midServer;
}

bool host::changeServer()
{
    close(_ser->getConnectFd());
    _ser->Connect(_balanceIp,_balancePort);
    string str;
    _ser->Recv(str);
    Json::Value val;
    Json::Reader read;
    if(-1 == read.parse(str.c_str(),val))
    {
        cerr <<"read json fail:errno:"<<endl;
        return false;
    }
    string ip = val["ip"].asString();
    short port = val["port"].asInt();

    close(_ser->getConnectFd());
    _ser->Connect(ip,port);
    return true;
}


bool host::sendToHost(const string &message)
{
    return _ser->Send(message);
}

bool host::recvFromHost(string &str)
{
    if(0 >= _ser->Recv(str))
    {
        changeServer();
        return false;
    }
    return true;
}

