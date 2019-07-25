/*************************************************************************
  > File Name: balanceServer.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/

#include "balanceServer.h"
using namespace std;
CNode_s::CNode_s()
{
    _vNodeCount = 0;
}

int CNode_s::getVNodeCount()
{
    return _vNodeCount;
}

void CNode_s::setData(const string &ip,unsigned short port)
{
    _ip = ip;
    _port = port;
}
string CNode_s::getIp()
{
    return _ip;
}
unsigned short CNode_s::getPort()
{
    return _port;
}
CNode_s::CNode_s(int count,const string &ip,unsigned short port)
{
    _vNodeCount = count;
    _ip = ip;
    _port = port;
}

CVirtualNode_s::CVirtualNode_s()
{
    _hash = -1;
    _node = NULL;
}

CVirtualNode_s::CVirtualNode_s(CNode_s * pNode)
{
    _hash = -1;
    _node = pNode;
}

void CVirtualNode_s::setNode_s(CNode_s *pNode)
{
    _node = pNode;
}

CNode_s *CVirtualNode_s::getNode_s()
{
    return _node;
}

void CVirtualNode_s::setHash(unsigned long pHash)
{
    _hash = pHash;
}

unsigned long CVirtualNode_s::getHash()
{
    return _hash;
}

long CMD5HashFun::getHashVal(const string& instr)
{
    int i;
    long hash = 0;
    unsigned char digest[16];
    /*调用MD5相关函数，生成instr的MD5码，存入digest*/
    MD5_CTX md5state;
    MD5_Init(&md5state);
    MD5_Update(&md5state, instr.c_str(), strlen(instr.c_str()));
    MD5_Final(digest,&md5state);
    cout<<instr<<endl;
    /* 每四个字节构成一个32位整数，
     *     将四个32位整数相加得到instr的hash值（可能溢出） */
    for(i = 0; i < 4; i++)
    {
        hash += ((long)(digest[i*4 + 3]&0xFF) << 24)
            | ((long)(digest[i*4 + 2]&0xFF) << 16)
            | ((long)(digest[i*4 + 1]&0xFF) <<  8)
            | ((long)(digest[i*4 + 0]&0xFF));
    }
    return hash;
}

CConHash::CConHash(CHashFun * pFunc)
{
    /*设置hash函数*/
    if(pFunc == NULL) return;
    this->_func = pFunc;
    this->vNodes = 0;
    this->vnode_map = new map<unsigned long,CVirtualNode_s *> ();
}

void CConHash::setFunc(CHashFun *pFunc)
{
    _func = pFunc;
}

int CConHash::addNode_s(CNode_s * pNode)
{
    if(pNode == NULL) return -1;
    int vCount = pNode->getVNodeCount();
    if(vCount <= 0) return -1;

    CVirtualNode_s * virtualNode;

    char str [100];
    char num[10];

    string ip = pNode ->getIp();
    unsigned short port = pNode ->getPort();

    char port_str[10];
    sprintf(port_str,"%d",port);
    string sock = ip + port_str;

    strcpy(str,sock.c_str());
    unsigned long hash = 0;
    /*生成虚拟结点并插入到map中*/
    /*5倍基数扩大vCount，解决哈希冲突*/
    int base = 5*vCount;
    for(int i=0;i < vCount;++i)
    {
        virtualNode = new CVirtualNode_s(pNode);
        /*采用str+“i”的方法产生不同的iden串，用于后面的hash值计算*/
        //itoa(i,num,10);
        sprintf(num,"%d",i);
        strcat(str,num);
        /*得到散列的哈希值*/
        hash = _func->getHashVal(str);
        virtualNode->setHash(hash);
        /*当前虚拟节点不存在的情况下，保存该虚拟节点*/
        map<unsigned long,CVirtualNode_s *>:: iterator it;
        it = vnode_map->find(hash);
        if(it == vnode_map->end())
        {
            if(virtualNode != NULL)
            {
                /*需要判断，hash值左右的范围，如果距离它最近的hash值范围过小，则不均匀，要舍弃*/
                vnode_map->insert(make_pair(hash,virtualNode));
                this->vNodes++;
            }
        }
        else
        {
            cout <<"发现冲突，hash = "<<hash<<endl;
        }
    }
    cout <<"*****************************打印虚拟节点***********************************"<<endl;
    map<unsigned long,CVirtualNode_s *>::iterator it = vnode_map->begin();
    if(it == vnode_map->end()) cout <<"不存在虚拟节点"<<endl;
    for(;it != vnode_map->end();++it)
    {
        cout <<"hash = "<<it->first<<"     ----->ip = "<<it->second->getNode_s()->getIp()<<", port = "<<it->second->getNode_s()->getPort()<<endl;
    }
    cout<<"||||||||||||||||||||*********打印虚拟节点|***********||||||||||||||||||||||||"<<endl;
    return 0;
}
int CConHash::delNode_s(CNode_s * pNode)
{
    if(pNode==NULL) return -1;
    char str [100];
    char num [10];
    string ip = pNode ->getIp();
    short port = pNode ->getPort();

    char port_str[10];
    sprintf(port_str,"%d",port);
    string sock = ip + port_str;

    strcpy(str,sock.c_str()); 
    int vCount = pNode->getVNodeCount();
    unsigned long hash = 0;
    /*将该实体结点产生的所有虚拟结点进行删除*/
    for(int i=0;i<vCount;i++)
    {
        //itoa(i,num,10);
        sprintf(num,"%d",i);
        strcat(str,num);/*采用该方法还原iden串*/
        hash = _func->getHashVal(str);
        vnode_map->erase(hash);
    }
    cout <<"*****************************打印虚拟节点***********************************"<<endl;
    map<unsigned long,CVirtualNode_s *>::iterator it = vnode_map->begin();
    if(it == vnode_map->end()) cout <<"不存在虚拟节点"<<endl;
    for(;it != vnode_map->end();++it)
    {
        cout <<"hash = "<<it->first<<"     ----->ip = "<<it->second->getNode_s()->getIp()<<", port = "<<it->second->getNode_s()->getPort()<<endl;
    }
    cout<<"||||||||||||||||||||*********打印虚拟节点***********|||||||||||||||||||||||||"<<endl;
    return 0;
}

CNode_s * CConHash::lookupNode_s(const string & object)
{
    unsigned long key = this->_func->getHashVal(object);
    /*在map中查找key值比key大的最小的结点*/
    map<unsigned long,CVirtualNode_s *> ::iterator it;
    it = vnode_map->lower_bound(key);
    if(it == vnode_map->end())
    {
        it = vnode_map->begin();
    }
    CVirtualNode_s *rbNode = it->second;

    if(rbNode!=NULL)
    {
        return rbNode->getNode_s();
    }
    return NULL;
}


int CConHash::getVNodes()
{
    return this->vNodes;
}

event_base *balanceServer::_base = NULL;
CConHash* balanceServer::_hash = NULL; 
tcpServer* balanceServer::_balanceSer_server = NULL;
tcpServer* balanceServer::_balanceSer_client = NULL;
map<int,CNode_s *> * balanceServer::_serverStore = NULL;
map<int,struct event *> * balanceServer::_eventStore =NULL;
balanceServer::balanceServer()
{
    /*定义hash函数*/
    CHashFun * func = new CMD5HashFun();
    /*创建一致性hash对象*/
    CConHash * conhash = new CConHash(func);


    string acceptSerIp;
    unsigned short acceptSerPort;
    cout <<"input ip accept server:";
    cin >>acceptSerIp;
    cout <<"input port accept server:";
    cin >>acceptSerPort;

    _balanceSer_server = new tcpServer(acceptSerIp,acceptSerPort);

    string acceptCliIp;
    unsigned short acceptCliPort;
    cout <<"input ip accept client:";
    cin >>acceptCliIp;
    cout <<"input port accept client:";
    cin >>acceptCliPort;

    _balanceSer_client = new tcpServer(acceptCliIp,acceptCliPort);

    _hash = new CConHash(func);
    _base = event_base_new();
    _serverStore = new map<int,CNode_s *> ();
    _eventStore = new map<int ,struct event *> ();

    //监听服务器事件
    struct event *listenEventSer = event_new(_base,_balanceSer_server->getListenFd(),EV_READ | EV_PERSIST,balanceServer::listenCb_server,_balanceSer_server);
    if(NULL == listenEventSer)
    {
        cerr <<"balance_server listen event fail;errno:"<<errno<<endl;
        return ;
    }
    event_add(listenEventSer,NULL);
    cout <<"balance_server libevent start"<<endl;

    //监听客户端事件

    struct event *listenEventCli = event_new(_base,_balanceSer_client->getListenFd(),EV_READ | EV_PERSIST,balanceServer::listenCb_client,_balanceSer_client);
    if(NULL == listenEventCli)
    {
        cerr <<"balance_client listen event fail;errno:"<<errno<<endl;
        return;
    }
    event_add(listenEventCli,NULL);
    cout <<"balance_client libevent start"<<endl;


    event_base_dispatch(_base); //等待触发
    //启动线程进行循环监听


}



void balanceServer::listenCb_server(int fd,short event,void *arg)
{
    tcpServer *listenCb_server = static_cast<tcpServer *>(arg);
    int cliFd = listenCb_server->Accept();
    if(-1 == cliFd)
    {
        cerr <<"balance_server accept fail;errno: "<<errno<<endl;
        return;
    }
    /*保存套接字和事件，libevent取消监听时用到*/
    struct event* cliEvent = event_new(_base,cliFd,EV_READ|EV_PERSIST,balanceServer::cliCb_server,listenCb_server);
    if(NULL == cliEvent) 
    {
        cerr <<"balance  new fail;errno:"<<errno<<endl;
        return;
    }
    _eventStore->insert(make_pair(cliFd,cliEvent));
    event_add(cliEvent,NULL);
}


void balanceServer::cliCb_server(int fd,short event,void *arg)
{

    tcpServer *server = static_cast<tcpServer*>(arg);
    string info;
    if(0 >= server->Recv(fd,info))
    {
        cerr <<"server cli down;errno:0"<<errno<<endl;

        /*取消监听客户端套接字*/
        map<int ,struct event *> ::iterator itee = _eventStore->find(fd);
        if(itee != _eventStore->end())
        {
            event_free(itee->second);
            _eventStore->erase(fd);
        }
        /*删除已经掉线的服务器*/
        map<int,CNode_s *>::iterator it =_serverStore->find(fd);
        if(it != _serverStore->end())
        {
            CNode_s * node_s = it->second;
            _hash->delNode_s(node_s);
            cout <<"删除服务器：ip = "<<node_s->getIp()<<",port = "<< node_s->getPort()<<endl;
            delete node_s;
            node_s = NULL;
            _serverStore->erase(fd);
        }
        cout <<"*****************************打印负载均衡中存储的服务器***********************************"<<endl;
        map<int,CNode_s *>::iterator ite = _serverStore->begin();
        if(ite == _serverStore->end()) cout <<"负载均衡中未存储服务器"<<endl;
        for(;ite != _serverStore->end();++ite)
        {
            cout <<"cliFd= "<<ite->first<<"     ----->ip = "<<ite->second->getIp()<<", port = "<<ite->second->getPort()<<endl;
        }
        cout<<"||||||||||||||||||||**********打印负载均衡中存储的服务器**********||||||||||||||||||||||||||"<<endl;
        close(fd);
    }
    else
    {
        Json::Value val;
        Json::Reader read;
        if(read.parse(info.c_str(),val) == 0)
        {
            cerr <<"read fail;errno:"<<errno<<endl;
        }
        string temp = val["ip"].toStyledString();
        temp[temp.size() - 2] = 0;
        string ip = temp.c_str() + 1; 
        short port = val["port"].asInt();

        CNode_s * node_s = new CNode_s(10,ip,port);
        _hash->addNode_s(node_s);
        _serverStore->insert(make_pair(fd,node_s));
        cout <<"监听服务器：ip = "<<ip<<",port = "<< port<<endl;
        cout <<"*****************************打印负载均衡中存储的服务器***********************************"<<endl;
        map<int,CNode_s *>::iterator it = _serverStore->begin();
        if(it == _serverStore->end())
        {
            cout <<"负载均衡中未存储服务器"<<endl;
        }
        for(;it != _serverStore->end();++it)
        {
            cout <<"cliFd= "<<it->first<<"     ----->ip = "<<it->second->getIp()<<", port = "<<it->second->getPort()<<endl;
        }
        cout<<"||||||||||||||||||||**********打印负载均衡中存储的服务器**********||||||||||||||||||||||||||"<<endl;

    }
}
void balanceServer::listenCb_client(int fd,short event,void *arg)
{
    tcpServer *listenCb_client = static_cast<tcpServer *>(arg);
    int cliFd = listenCb_client->Accept();
    if(-1 == cliFd)
    {
        cerr <<"balance_server accept fail;errno: "<<errno<<endl;
        return;
    }
    /*说明有客户端请求连接，解析请求连接的IP和PORT*/

    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);

    if(!getpeername(cliFd,(struct sockaddr *)&caddr,&len))
    {
        cout <<"client IP: "<<inet_ntoa(caddr.sin_addr)<<endl;
        cout <<"client port: "<<ntohs(caddr.sin_port)<<endl;
    }
    string ip = inet_ntoa(caddr.sin_addr);
    short port = ntohs(caddr.sin_port);

    string node;
    char port_str[10];
    sprintf(port_str,"%d",port);
    node = ip + port_str;

    CNode_s *s = _hash->lookupNode_s(node);

    ip = s->getIp();
    port = s->getPort();
    cout <<"ip: "<<ip<<"\n"<<"port:"<<port<<endl;
    Json ::Value val;
    val["ip"] = ip;
    val["port"] = port;
    //_hash对象负责解析，得到ip和port发送给clifd

    _balanceSer_client->Send(cliFd,val.toStyledString());

}
