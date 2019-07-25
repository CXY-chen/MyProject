/*************************************************************************
  > File Name: selectServer.cpp
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sun 02 Dec 2018 08:51:14 PM CST
 ************************************************************************/

#include "selectServer.h"
#include <stdlib.h>
using namespace std;
/*
 *监听套接字的回调函数
 */
event_base *selectServer::_base = NULL;
map<int ,struct event *> selectServer::_eventMap;


/*
 *接受连接
 */
void selectServer::listenCb(int fd,short event,void *arg)
{
    tcpServer *server = static_cast<tcpServer*>(arg);
    int cliFd = server->Accept();
    if(-1 == cliFd)
    {
        cerr<<"select cli acccept fail;errno:"<<errno<<endl;
        return;
    }
    struct event* cliEvent = event_new(_base,cliFd,EV_READ|EV_PERSIST, selectServer::cliCb,server);
    if(NULL == cliEvent) 
    {
        cerr <<"select new fail;errno:"<<errno<<endl;
        return;
    }
    /*
     *保存,删除用到
     */
    _eventMap.insert(make_pair(cliFd,cliEvent));
    event_add(cliEvent,NULL); //
    cout<< "slecterSer create success"<<endl;
}

/*
 *  客户端套接字的回调函数
 */
void selectServer::cliCb(int fd,short event,void *arg)
{
    tcpServer *server = static_cast<tcpServer*>(arg);
    string id;
    if(0 >= server->Recv(fd,id))
    {
        cerr <<"select cli down;errno:0"<<errno<<endl;
        event_free(_eventMap[fd]);
        _eventMap.erase(fd);
        close(fd);
        return;
    }
    Json::Value val;
    val["type"] = SELECT;
    val["fd"] = fd;
    val["id"] = id;

    //host send to mainserver
    host::getHost()->sendToHost(val.toStyledString());

}

//启动线程循环监听
void *selectServer::selectThreadRun(void *arg)
{
    event_base_dispatch(_base); //等待触发，
}


selectServer::selectServer()
{
    //输入信息采集服务器的端口
    unsigned short port;
    cout <<"select_server ip = 127.0.0.1"<<endl;
    cout << "please input select_server port"<<endl;

    cin >> port;
    cout <<"server listen event create success"<<endl;

    //创建分布式信息采集服务器
    _selectSer = new tcpServer("127.0.0.1",port);

    //libevent
    _base = event_base_new();

    //  创建监听事件
    struct event *listenEvent = event_new(_base,_selectSer->getListenFd(),EV_READ|EV_PERSIST,selectServer::listenCb,_selectSer);
    if(NULL == listenEvent)
    {
        cerr <<"select ser listen event create fail;errno:"<<errno<<endl;
        exit(0);
    }
    event_add(listenEvent,NULL);
cout <<"select_server libevent start"<<endl;
    //启动线程进行循环监听
    pthread_t pid;
    pthread_create(&pid,NULL,selectServer::selectThreadRun,_base);
}
//发送数据给信息采集机
void selectServer::sendSelect(int fd,string &str)
{
    _selectSer->Send(fd,str);
}

