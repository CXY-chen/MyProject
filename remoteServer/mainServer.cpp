/*************************************************************************
	> File Name: mainServer.cpp
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#include "mainServer.h"
using namespace std;

remoteServer *remoteServer::_mainServer = NULL;

remoteServer::remoteServer(const string &ip,short port)
{
    _server = new tcpServer(ip,port);
    _client = new tcpClient();
    cout <<"balance server ip = 127.0.0.1"<<endl;
    cout <<"input balance server port:";
    string _ip = "127.0.0.1";
    short _port;
    cin >>_port;
    _client->Connect(_ip,_port);
    Json::Value val;
    val["ip"] = ip;
    val["port"] = port;
    _client->Send(val.toStyledString());
    cout <<"send ip = "<<ip<<"\nport = "<<port<<endl;
}

remoteServer* remoteServer::getServer()
{
    if(_mainServer == NULL)
    {
        
        if(_mainServer == NULL)
        {
    cout <<"ip = 127.0.0.1"<<endl;
    cout <<"please input server port"<<endl;
    string ip;
    ip = "127.0.0.1";
    short port;
    cin>>port;
            _mainServer = new remoteServer(ip,port);
        }
    }
    return _mainServer;
}
int remoteServer::Recv(int fd,string &str)
{
    return _server->Recv(fd,str);
}

int remoteServer::Send(int fd,const string &str)
{
    return _server->Send(fd,str);
}
int remoteServer::getListenFd()
{
    return _server->getListenFd();
}
int remoteServer::Accept()
{
    return _server->Accept();
}
