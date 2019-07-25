/*************************************************************************
  > File Name: pthreadPool.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/

#include "pthreadPool.h"
using namespace std;
pthreadPool::pthreadPool(int num,struct event_base* base)
{
    cout <<"pthread pool create......"<<endl;
    for(int i = 0; i < num; i++)
    {
        /*
         *利用socketpair通信
         */
        int arr[2] = {0};
        socketpair(AF_UNIX,SOCK_STREAM,0,arr);

        /*
         *监听socketpair的0端
         */
        struct event*socketpairEvent = event_new(base,arr[0],EV_READ | EV_PERSIST,pthreadPool::recvEventNumFromThread,&_pthreadEventNumMap);
   
        if(NULL == socketpairEvent)
        {
            cerr <<"socketpair event create fail;errno"<<errno<<endl;
            exit(0);
        }
        event_add(socketpairEvent,NULL);

        cout <<"socket pair "<< i<<"create success"<<endl;

        _pthreadEventNumMap.insert(make_pair(arr[0],0));
        /*
         *起线程
         */
        new pthread(arr[1]);
        cout <<"pthread: "<<i<<" create"<<endl;
    }
}
/*
 *线程池将接受连接得到的clifd交给num值最小的线程，num加一
 */
void pthreadPool::sendCliFdToPthread(int fd)
{
    map<int,int>::iterator it = _pthreadEventNumMap.begin();
    map<int,int>::iterator tmp = it;
    int eventNum = it->second;
    for(;it != _pthreadEventNumMap.end();it++)
    {
        cout <<"pthread show:"<<it->first<<"   event num"<< it->second<<endl;
        if(it->second < eventNum)
        {
            tmp = it;
        }
    }
    /*
     *将clifd通过socket对传送到另一端，send
     */
    send(tmp->first,(char *)&fd,4,0);
    tmp->second++;
    cout <<"send cliFd to pthread: "<<tmp->first<<endl;
}

/*
 *接受线程的回馈信息
 */
void pthreadPool::recvEventNumFromThread(int fd,short event,void *arg)
{
    map<int,int> *_map = static_cast<map<int,int>*>(arg);
    int num;
    recv(fd,(char *)&num,4,0);
    (*_map)[fd] = num;
}

