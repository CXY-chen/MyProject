/*************************************************************************
  > File Name: selecter.cpp
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#include "selecter.h"
using namespace std;
selecter::selecter()
{
    _selectClient = new tcpClient();
    cout <<"connect select_server IP = 127.0.01";
    string ip = "127.0.0.1";
    short port;
cout <<"input selecter port:"<<endl;
cin >>port;
    if(-1 == _selectClient->Connect(ip,port))
    {
        exit(0);
    }
}
void selecter::select()
{
    string id;
    cout <<"please cin id"<<endl;
    cin >>id;
    _selectClient->Send(id);


    string buff;
    _selectClient->Recv(buff);
    cout<<buff<<endl;
}


