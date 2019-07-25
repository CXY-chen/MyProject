/*************************************************************************
	> File Name: server.cpp
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/
#include "server.h"
using namespace std;
server::server()
{
    /*
     * 启动libevent
     */
    _base = event_base_new();
    cout <<"/**main_server libevent start**/"<<endl;

    /*
     *启动线程池
     */
    cout <<"please cin pthread num:(3)"<<endl;

    int num;
    cin >>num;
    /*
     *将base传入线程池中，将线程池中创建的socketpair0端加入监听   */
    _pthreadPool = new pthreadPool(num,_base);
    cout <<"pthreadpool create success"<<endl;
}
void server::run()
{
    sleep(1);
    cout <<"**开始连接数据库**"<<endl;
    database::getDatabase();
    cout <<"database is working..."<<endl;
    /*
     *先得到实际负责通的服务器，单例模式 */
    cout <<"**开始启动服务器**"<<endl;
    remoteServer::getServer(); 
    cout <<"server is working..."<<endl;
    /*
     *创建监听事件
     */
    struct event *listenEvent = event_new(_base,remoteServer::getServer()->getListenFd(),EV_READ | EV_PERSIST,server::listenCb,_pthreadPool);
    if(NULL == listenEvent)
    {
        cerr <<"listen event create fail;errno"<<errno<<endl;
        exit(0);
    }
    event_add(listenEvent,NULL);

    cout <<"server listen event create success"<<endl;
    /*
     *线程池创建成功，服务器启动，开始循环监听
     */ event_base_dispatch(_base);
}
/*
 *libevent监听连接套接字的回调函数，当listenfd有数据时触发
 */
void server::listenCb(int fd,short event,void *arg)
{
    cout <<"request accept"<<endl;
    pthreadPool *pool = static_cast<pthreadPool *>(arg);

    /*
     *接受客户端连接
     */
    int cliFd = remoteServer::getServer()->Accept();
    cout <<"cli conect success,clifd = "<<cliFd<<endl;

    /*
     *将客户端连接发送给线程池
     */
    pool->sendCliFdToPthread(cliFd);
}
