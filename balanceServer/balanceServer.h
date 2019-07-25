/*************************************************************************
  > File Name: balanceServer.h
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _BALANCESERVER_H
#define _BALANCESERVER_H
#include <iostream>
#include <string>
#include <map>
#include <event.h>
#include <errno.h>
#include <pthread.h>
#include <openssl/md5.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#include "tcpServer.h"
using namespace std;

/*实体结点*/
class CNode_s
{
    public:
        /*构造函数*/
        CNode_s();
        CNode_s(int count,const string &ip,unsigned short port);
        /*希构函数*/
      //  ~CNode_s(){}
        /*获取实体结点的虚拟结点数量*/
        int getVNodeCount();

        /*设置实体结点数据值*/
        void setData(const string &ip,unsigned short port);

        /*获取实体结点数据值*/
        string getIp();
        unsigned short getPort();
    private:
        void setCNode_s(int count,const string  &ip,short port);
        int _vNodeCount; /*虚拟结点数目*/
        string _ip;      /*数据结点*/
        unsigned short _port;
};

/*虚拟结点*/
class CVirtualNode_s
{
    public:
        /*构造函数*/
        CVirtualNode_s();
        CVirtualNode_s(CNode_s * pNode);
        /*希构函数*/
        ~CVirtualNode_s()
        {
            delete _node;
        }
        /*设置虚拟结点所指向的实体结点*/
        void setNode_s(CNode_s * pNode);

        /*获取虚拟结点所指向的实体结点*/
        CNode_s * getNode_s();

        /*设置虚拟结点hash值*/
        void setHash(unsigned long pHash);

        /*获取虚拟结点hash值*/
        unsigned long getHash();
    private:
        unsigned long _hash; /*hash值*/
        CNode_s * _node; /*虚拟结点所指向的实体结点*/
};
/*定义Hash函数类接口，用于计算结点的hash值*/

class CHashFun
{
    public:
        virtual long getHashVal(const string &address) = 0;
};
/*用MD5算法计算结点的hash值，继承CHashFun父类*/
class CMD5HashFun : public CHashFun
{
    public:
        virtual long getHashVal (const string &address);
};
class CConHash
{
    public:
        /*构造函数*/
        CConHash(CHashFun * pFunc);
        /*系构函数*/
        ~CConHash()
        {
            if(_func != NULL)delete _func;
            if(vnode_map != NULL)delete vnode_map;
        }
        /*设置hash函数*/
        void setFunc(CHashFun * pFunc);

        /*增加实体结点 , 0代表成功 , -1代表失败*/
        int addNode_s(CNode_s * pNode);

        /*删除实体结点 , 0代表成功 , -1代表失败*/
        int delNode_s(CNode_s * pNode);

        /*查找实体结点*/
        CNode_s * lookupNode_s(const string &object);

        /*获取一致性hash结构的所有虚拟结点数量*/
        int getVNodes();
    private:
        /*Hash函数*/
        CHashFun * _func;
        /*虚拟结点总个数*/
        int vNodes;
        /*存储虚拟节点的map*/
        map<unsigned long,CVirtualNode_s *> *vnode_map;

};

class balanceServer
{
    public:
        balanceServer();
        static void cliCb_server(int fd,short event,void *arg);
        static void listenCb_server(int fd,short event,void *arg);
        static void listenCb_client(int fd,short event,void *arg);
        static void *balanceThreadRun(void *arg);
    private:

        static tcpServer *_balanceSer_server;
        static tcpServer *_balanceSer_client;
        static event_base *_base;
        static CConHash * _hash;
        static map<int,CNode_s *> *_serverStore;
        static map<int,struct event *> *_eventStore;
};
#endif
