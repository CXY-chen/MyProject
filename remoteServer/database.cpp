/*************************************************************************
  > File Name: database.cpp
  > Author: 陈玺印 
  > Mail: 1278500458@qq.com 
 ************************************************************************/
#include <stdio.h> 
#include "database.h"
#include <string.h>
using namespace std;
/*
   enum result
   {
   EXECUTE_FAIL = 1,
   ALREADY_EXIST,
   INSERT_SUCCESS,
   DELETE_SUCCESS,
   UPDATE_SUCCESS,
   INEXSITENCE,
   }
   */
database *database::_data = NULL;
database *database::getDatabase()
{
    if(_data == NULL)
    {
        if(_data == NULL)
        {
            string user;
            string pw;
            string data;
            cout <<"input user:"<<endl;
            cin >> user;
            cout <<"input pw:"<<endl;
            cin >> pw;
            cout <<"input database:"<<endl;
            cin >> data;
            _data = new database(user,pw,data);
        }
    }
    return _data;
}
database::database(const string &user,const string &pw,const string &database)
{
    _mysql = mysql_init((MYSQL*)0);
    if(!mysql_real_connect(_mysql,"127.0.0.1",user.data(),pw.data(),NULL,3306,NULL,0))
    {
        cerr<<"mysql connect failed!Reason:"<<mysql_error(_mysql)<<endl;
        return;
    }
    if(mysql_select_db(_mysql,database.data()))
    {
        cerr<<"select database fail;errno:"<<errno<<endl;
        Close();
        return;
    }
    cout <<"mysql connect success"<<endl;
}

int database::Login(const string &name,const string &pw)
{
    string n = name;
    n[n.size() -2] = 0;
    string p = pw;
    p[p.size() -2] = 0;
    char query[124];
    sprintf(query,"select *from manager where name = '%s' and pw = '%s';",n.c_str()+1,p.c_str()+1);

    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }

    MYSQL_RES *result = mysql_store_result(_mysql);
    if(mysql_num_rows(result) == 0)
    {
        return INEXSITENCE;
    }
    else
    {
        return ALREADY_EXSIT;
    }
}

int database::Register(const string &name,const string &pw)
{
    string n = name;
    n[n.size() -2] = 0;
    string p = pw;
    p[p.size() -2] = 0;

    char query[124];
    sprintf(query,"select *from manager where name = '%s' and pw = '%s';",n.c_str()+1,p.c_str()+1);
    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }
    MYSQL_RES *result = mysql_store_result(_mysql);
    if(mysql_num_rows(result))
    {
        return ALREADY_EXSIT;
    }
    mysql_free_result(result);
  /*  MYSQL_RES * pRes;
    int nError = mysql_query(m_pConn, strSQL);

    do 
    {
        pRes = mysql_use_result(_mysql);
        mysql_free_result(pRes);
    } while (!mysql_next_result(_mysql));
    */
    char query1[124];
    sprintf(query1,"INSERT INTO manager values('%s','%s');",n.c_str() + 1,p.c_str()+1);
    cout <<query1<<endl;
    if(mysql_query(_mysql,query1))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }
    else
    {
        return INSERT_SUCCESS;
    }
}

int database::Insert(const string &id,const string &name,const string &date,int limit)
{
    if (ALREADY_EXSIT == Select(id))
    {
        return ALREADY_EXSIT;
    }
    string _id = id;
    _id[_id.size() - 2] = 0;

    string _name = name;
    _name[_name.size() - 2] = 0;

    string _date = date;
    _date[_date.size() - 2] = 0;

    char query[124];
    sprintf(query,"INSERT INTO visitors values('%s','%s','%s','%d');",_id.c_str() + 1,_name.c_str() + 1,_date.c_str() + 1,limit);
    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }
    else
    {
        return INSERT_SUCCESS;
    }
}


int database::Delete(const string &id)
{
    if(Select(id) != ALREADY_EXSIT)
    {
        return INEXSITENCE;
    }
    string _id = id;
    _id[_id.size() - 2] = 0;
    char query[124];
    sprintf(query,"delete from  visitors where id = '%s';",_id.c_str() + 1);
    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }
    else
    {
        return DELETE_SUCCESS;
    }
}

int database::Select(const string &id)
{
    string _id = id;
    _id[_id.size() - 2] = 0;
    cout <<"_id:  "<<_id;
    char query[124];
    sprintf(query,"select *from visitors where id = '%s';",_id.c_str() + 1);
    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }

    MYSQL_RES *result = mysql_store_result(_mysql);

    if(mysql_num_rows(result) == 0)
    {
        return INEXSITENCE;
    }
    else
    {
        return ALREADY_EXSIT;
    }
    mysql_free_result(result);

}

int database::Update(const string &id,const string &name,const string &date,int limit)
{
    if(Select(id) != ALREADY_EXSIT)
    {
        return INEXSITENCE;
    }
    string _id = id;
    _id[_id.size() - 2] = 0;

    string _name = name;
    _name[_name.size() - 2] = 0;

    string _date = date;
    _date[_date.size() - 2] = 0;


    char query[124];
    sprintf(query,"update visitors set name = '%s',date = '%s',limit = '%d' where id = '%s';",_name.c_str() + 1,_date.c_str() + 1,limit,_id.c_str() + 1);
    cout <<query<<endl;
    if(mysql_query(_mysql,query))
    {
        cerr<<"Execute fail!Reason:"<<mysql_error(_mysql)<<endl;
        Close();
        return EXECUTE_FAIL;
    }
    MYSQL_RES *result = mysql_store_result(_mysql);
    result = mysql_store_result(_mysql);
    if(NULL == result)
    {
        return EXECUTE_FAIL;
    }
    else
    {
        return UPDATE_SUCCESS;
    }

}

void database::Close()
{
    mysql_close(_mysql);
}
