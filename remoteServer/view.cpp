/*************************************************************************
	> File Name: view.cpp
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#include "view.h"
using namespace std;
void viewInsert::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string name = val["name"].toStyledString();
    string id = val["id"].toStyledString();
    string date = val["date"].toStyledString();
    int limit = val["limit"].asInt();
    string re;
    int result = _database->Insert(id,name,date,limit);
    if(result == INSERT_SUCCESS)
    {
        re = "insert success";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "insert fail";
        }
        if(result == ALREADY_EXSIT)
        {
            re = "already exsit";
        }
    }
    Json::Value reback;
    reback["massage"] = re.c_str();
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());

    cout <<"Insert operation"<<endl;
}
void viewDelete::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    cout <<data<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string id = val["id"].toStyledString();
    int result = _database->Delete(id);
    string re;
    if(result == DELETE_SUCCESS)
    {
        re = "delete success";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "delete fail";
        }
        if(result == INEXSITENCE)
        {
            re = "inexsitence";
        }
    }
    Json::Value reback;
    reback["massage"] = re.c_str();
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());
    cout <<"Delete operation"<<endl;
}
void viewUpdate::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    cout <<data<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string id = val["id"].toStyledString();
    string name = val["name"].toStyledString();
    string date = val["date"].toStyledString();
    int limit = val["limit"].asInt();
    int result = _database->Update(id,name,date,limit);
    string re;
    if(result == UPDATE_SUCCESS)
    {
        re = "update success";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "update fail";
        }
        if(result == INEXSITENCE)
        {
            re = "inexsitence";
        }
    }
    Json::Value reback;
    reback["massage"] = re.c_str();
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());
    cout <<"Update operation"<<endl;
}


void viewFind::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    cout <<data<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string id = val["id"].toStyledString();
    int result = _database->Select(id);
    string re;
    if(result == ALREADY_EXSIT)
    {
        re = "exsit";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "select fail";
        }
        if(result == INEXSITENCE)
        {
            re = "inexsitence";
        }
    }
    Json::Value reback;
    reback["massage"] = re;
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());
    cout <<"Select operation"<<endl;
}



void viewRegister::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    cout <<data<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string name = val["name"].toStyledString();
    string pw = val["pw"].toStyledString();
    
    cout <<val<<"fd:"<<fd<<endl;
    
    int result = _database->Register(name,pw);

    string re;
    if(result == INSERT_SUCCESS)
    {
        re = "register success";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "register fail";
        }
        if(result == ALREADY_EXSIT)
        {
            re = "manager exsit";
        }
    }
    Json::Value reback;
    reback["massage"] = re.c_str();
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());
    cout <<"Register operation"<<endl;
}


void viewLogin::view_handle(int cliFd,const string &data)
{
    database *_database = database::getDatabase();
    cout <<data<<endl;
    Json::Value val;
    Json::Reader read;
    if(read.parse(data.c_str(),val) == 0)
    {
        cerr <<"read fail;errno:"<<errno<<endl;
    }
    int type = val["type"].asInt();
    int fd = val["fd"].asInt();
    string name = val["name"].toStyledString();
    string pw = val["pw"].toStyledString();

    int result = _database->Login(name,pw);
    
    string re;
    if(result == ALREADY_EXSIT)
    {
        re = "login success";
    }
    else
    {
        if(result == EXECUTE_FAIL)
        {
            re = "login fail";
        }
        if(result == INEXSITENCE)
        {
            re = "manager inexsit";
        }
    }
    Json::Value reback;
    reback["massage"]  = re;
    reback["fd"] = fd;
    reback["type"] = type;
    remoteServer::getServer()->Send(cliFd,reback.toStyledString());
    cout <<"Login operation"<<endl;
}
