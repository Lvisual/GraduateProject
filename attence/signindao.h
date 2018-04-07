#ifndef SIGNINDAO_H
#define SIGNINDAO_H

#include <QObject>
#include <QObject>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include "signinmodel.h"

class SignIn;
class SignInDao : public QObject
{
    Q_OBJECT
    const QString dataBaseName = "SignInTable";

    QString create_sql = "create table if not exists "+dataBaseName
            +"(id integer primary key, name varchar,agent varchar,signdate varchar,signtime varchar,status varchar,remark varchar)";
    QString select_max_sql = "select max(id) from "+dataBaseName;
    QString insert_sql = "insert into "+dataBaseName+"(id,name,agent,signdate,signtime,status,remark) values(?,?,?,?,?,?,?)";
    QString update_sql = "update "+dataBaseName+"set name:=name,agent:=agent,signdate:=signdate,signtime:=signtime,status:=status,remark:=remark where id=:id";
    QString select_all_sql = "select id,name,agent,signdate,signtime,status,remark from "+dataBaseName;
    QString select_id_sql = "select * from "+dataBaseName+" where id =?";
    //QString select_type_sql = "select typename from "+dataBaseName;
    QString delete_sql = "delete from "+dataBaseName+" where id =?";
    QString clear_sql = "delete from "+dataBaseName;
    QSqlDatabase db;// = QSqlDatabase::database("QSQLITE"); //建立数据库连接
    QSqlQuery* qry;
public:
    SignInDao();
    bool insert(SignIn s);            //出入数据
    QVector<SignIn> getPageList(SignIn info,int page = 1,int pageSize = 10);
    bool deleteById(int id);
    bool update(SignIn info);
    QVector<SignIn> selectById(int id);
    //QVector<QString> getType();
};


#endif // SIGNINDAO_H
