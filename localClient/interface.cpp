/*************************************************************************
  > File Name: interface.cpp
  > Author: 计献之 
  > Mail: 1841531744@qq.com 
  > Created Time: Sun 02 Dec 2018 08:38:43 PM CST
 ************************************************************************/
#include "interface.h"
using namespace std;

interface::interface()
{
    //创建分布式信息采集服务器的线程对象
    //
    host::getHost();
   cout<<"host_server start"<<endl;
    _selectSer = new selectServer();
    cout<<"select_server start"<<endl;
}

void* interface::recvFromHost(void *arg)
{
    selectServer *selectSer = static_cast<selectServer *>(arg);
    while(1)
    {
        string str;
        if(host::getHost()->recvFromHost(str))
        {
            //解析json
            Json::Value val;
            Json::Reader read;
            if(read.parse(str.c_str(),val) == 0)
            {
                cerr<<"read fail;errno:"<<errno<<endl;
                continue; 
            }
            //如果接受的数据属于信息采集机所有
            if(val["type"].asInt() == SELECT && val["fd"].asInt() != -1)
            {
                //发送给信息采集机
                int fd = val["fd"].asInt();
                string str = val["massage"].toStyledString();
                /*
                 *信息采集机服务器发送给信息采集机
                 */
                selectSer->sendSelect(fd,str);

            }
            else
            {
                //本机数据直接输出
                cout <<val["massage"]<<endl;
            }
        }
    }
}
/*
 *用户界面
 */
void interface::meun()
{

    cout << "**************************************************************" << endl;
    cout << "**                   1 信息录入                       ********" << endl;
    cout << "***                  2 信息删除                        *******" << endl;
    cout << "****                 3 信息修改                         ******" << endl;
    cout << "*****                4 信息查询                          *****" << endl;
    cout << "******               5 小游戏一                           ****" << endl;
    cout << "*******              6 小游戏二                            ***" << endl;
    cout << "********             0 退出系统                             **" << endl;
    cout << "**************************************************************" << endl;
    cout << "请输入你的选择:" ;
}

void interface::run()
{
    //创建从服务器接收数据的线程
    recvFromHost();
    while(1)
    {
        //用户选择
        sleep(1);
        meun();
        int choice;
        cin >> choice;
        switch(choice)
        {
            case 0:
                return ;
            case 1:  
                Insert();
                
                break;
            case 2:
                Delete();
                break;
            case 3:
                Update();
                break;
            case 4:
                Select();
                break;
            case 5:
                Paint_Heart();
                break;
            case 6:
                Paint_Rose();
            default:
                cout <<"error cin,please try again"<<endl;
                break;
        }
    }
}
void interface::Insert()
{
    string name;
    cout <<"please cin name"<<endl;
    cin >>name;

    string id;
    cout <<"please cin id"<<endl;
    cin >>id;

    string date;
    cout <<"please cin date(ex,20181201)"<<endl;
    cin >>date;

    int time;
    cout <<"please cin tiem(day)"<<endl;
    cin >>time;
    Json::Value val;
    val["fd"] = -1;
    val["type"] = INSERT;
    val["name"] = name;
    val["id"] = id;
    val["date"] = date;
    val["limit"] = time;
    host::getHost()->sendToHost(val.toStyledString());
    
}
void interface::Delete()
{
    string id;
    cout <<"cin id:"<<endl;
    cin >>id;
    Json::Value val;
    val["fd"] = -1;
    val["type"] = DELETE;
    val["id"] = id;
    host::getHost()->sendToHost(val.toStyledString());
   
}
void interface::Update()
{
    string name;
    cout <<"please cin name"<<endl;
    cin >>name;

    string id;
    cout <<"please cin id"<<endl;
    cin >>id;

    string date;
    cout <<"please cin date(ex,20181201)"<<endl;
    cin >>date;

    int time;
    cout <<"please cin tiem(day)"<<endl;
    cin >>time;
    Json::Value val;
    val["type"] = UPDATE;
    val["fd"] = -1;
    val["name"] = name;
    val["id"] = id;
    val["date"] = date;
    val["limit"] = time;
    host::getHost()->sendToHost(val.toStyledString());
}
void interface::Select()
{
    string id;
    cout <<"cin id:"<<endl;
    cin >>id;
    Json::Value val;
    val["fd"] = -1;
    val["type"] = SELECT;
    val["id"] = id;
    host::getHost()->sendToHost(val.toStyledString());
   
}
void interface::Paint_Heart()
{
    double x, y, a = 1.0, f;
    for (y = a + 0.3; y >= -a - 0.3; y -= 0.1)
    {
        for (x = -a - 0.3; x <= a + 0.3; x += 0.05)
        {
            f = pow(x*x + y * y, 3) - a * a * pow(x*x - y * y, 2);
            putchar(f <= 1E-5 ? '*' : ' ');
        }
        cout << endl;
    }
}
void interface::Paint_Rose()
{
    double x, y, f;
    for (y = 1.6; y >= -1.1; y -= 0.15)
    {
        for (x = -1.1; x <= 1.1; x += 0.05)
        {
            f = x * x + pow(y - pow(x*x, 1.0 / 3), 2) - 1;
            putchar(f <= 1E-5 ? '*' : ' ');
        }
        cout << endl;
    }
}

/*
 *启动专门从服务器接受数据的线程
 */
void interface::recvFromHost()
{
    pthread_t pid;
    pthread_create(&pid,NULL,interface::recvFromHost,_selectSer);
}

