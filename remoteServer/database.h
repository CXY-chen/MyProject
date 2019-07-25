/*************************************************************************
	> File Name: database.h
	> Author: 陈玺印 
	> Mail: 1278500458@qq.com 
 ************************************************************************/

#ifndef _DATABASE_H
#define _DATABASE_H
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <errno.h>
using namespace std;
enum result
{
    EXECUTE_FAIL = 1,
    ALREADY_EXSIT,
    INSERT_SUCCESS,
    DELETE_SUCCESS,
    UPDATE_SUCCESS,
    INEXSITENCE,
};
class database
{
    public:
        static database *getDatabase();
        int Login(const string &name,const string &pw);
        int Register(const string &name,const string &pw);
        int Insert(const string &id,const string &name,const string &date,int limit);
        int Delete(const string &id);
        int Select(const string &id);
        int Update(const string &id,const string &name,const string &date,int limit);
        void Close();
    private:
        database(const string &user,const string &pw,const string &database);
        MYSQL *_mysql;
        static database *_data;
};
#endif
