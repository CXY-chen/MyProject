/*************************************************************************
  > File Name: mpthred.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/
#include "mpthread.h"
using namespace std;
pthread::pthread(int socketpair_one)
{
    _base = event_base_new();
    /*
     *客户端套接字和事件的map表，删时用
     */
    _cliEventMap = new map<int ,struct event *>();
    /*
     *监听1端
     */
    struct event* socketpairEvent = event_new(_base,socketpair_one,EV_READ | EV_PERSIST,pthread::socketpairCb,this);
    if(NULL == socketpairEvent)
    {
        cerr <<"sock pair 1 event creat fail;errno:"<<errno<<endl;
        exit(0);
    }
    event_add(socketpairEvent,NULL);

    run();
}

void pthread::run()
{
    pthread_t pid;
    pthread_create(&pid,NULL,pthread::pthRun,_base);
}

void* pthread::pthRun(void *arg)
{
    cout <<"pthread "<<pthread_self()<<"running"<<endl;
    struct event_base * base = static_cast<struct event_base *>(arg);
    event_base_dispatch(base);
}

/*
 *监听1端，0端发来clifd时调用
 */
void pthread::socketpairCb(int fd,short event,void *arg)
{
    pthread *pth = static_cast<pthread *>(arg);
    int cliFd;
    recv(fd,(char *)&cliFd,4,0);
/*
 *监听客户端套接字，真正监听客户端套接字是在线程中,当客户端套接字有信号传入时，触发cliCb函数处理
 */
    struct event *cliEvent = event_new(pth->_base,cliFd,EV_READ | EV_PERSIST,pthread::cliCb,arg);
    if(NULL == cliEvent)
    {
        cerr << "cli event create fail;errno:"<<errno<<endl;
        return ;
    }
    event_add(cliEvent,NULL);
    pth->_cliEventMap->insert(make_pair(cliFd,cliEvent));
}

void pthread::cliCb(int fd,short event,void *arg)
{
    cout <<"cli fd:"<<fd<<" new massage"<<endl;
    cout <<"process pthread: "<<pthread_self()<<" " <<endl;
    pthread *pth = static_cast<pthread *>(arg);
    string tmp;
    int flage = 0; 
    flage = remoteServer::getServer()->Recv(fd,tmp);
    if(flage == 0)
    {
        cerr <<"cli down clifd"<< fd <<endl;
        event_free((*pth->_cliEventMap)[fd]);
        pth->_cliEventMap->erase(fd);
        close(fd);
    }
  cout <<"线程接收到来自客户端的包！"<<endl; 
    cout <<tmp<<endl;
   /*
    *mvc模式转向控制台处理
    */
    cout <<"将线程收据传到控制台做处理！"<<endl;
    controller *_control = controller::getController();
    _control->process(fd,tmp);
    /*int type = val["type"].asInt();
    switch(type)
    {
        case PEGISTER:

        case LOGIN:
        case EXIT:
        case INSERT:
        case DELETE:
        case UPDATE:
        case SELECT:
        defaultp
    }
    */

    /*
     *以下为测试代码
     */

    /*
     *
    string reback = "login success";
    remoteServer::getServer()->Send(fd,reback);
    */
}

