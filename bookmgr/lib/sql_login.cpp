#include "sql_login.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
sql_login* sql_login::instance = nullptr;
sql_login::sql_login() {}

void sql_login::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    QString strPath = QCoreApplication::applicationDirPath()+"/db/book.db";
    m_db.setDatabaseName(strPath);
    m_db.open();
}

QString sql_login::Login(QString strUser, QString strPassword)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where user_name='%1' and password_hash='%2'").arg(strUser, strPassword);
    QString strSql1 = QString("select * from user where user_name='%1'").arg(strUser);
    q.exec(strSql);
    bool ret;
    if(q.next())
        ret = 1;
    else
        ret = 0;
    if(!ret)
    {
        strUser = "";
    }
    q.exec(strSql1);
    if(q.next())
        ret = 1;
    else
        ret = 0;
    if(ret && strUser == "")
    {
        strUser = " " + strUser;
    }
    return strUser;
}

bool sql_login::Judge_role(QString strUser)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where user_name='%1' and role='用户'").arg(strUser);
    q.exec(strSql);
    bool ret;
    if(q.next())
        ret = 1;
    else
        ret = 0;
    return ret;
}

int sql_login::Get_id(QString strUser)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where user_name='%1' and role='用户'").arg(strUser);
    q.exec(strSql);
    q.next();
    int res = q.value(0).toInt();
    return res;
}

bool sql_login::Register(QString strUser, QString strPassword, QString strTname, QString strPhone)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where user_name='%1'").arg(strUser);
    q.exec(strSql);
    bool ret;
    if(q.next())
        ret = 1;
    else
        ret = 0;
    if(!ret)
    {
        strSql = QString("insert into user VALUES(NULL,'%1','%2','用户','%3', '%4', '良好')").arg(strUser, strPassword, strTname, strPhone);
        q.exec(strSql);
    }
    return !ret;
}
