#ifndef EMPLOYEEDAO_H
#define EMPLOYEEDAO_H

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
#include "employeemodel.h"

class Employee;
class employeeDao : public QObject
{
    Q_OBJECT
    const QString dataBaseName = "employeeTable";

    QString create_sql = "create table if not exists "+dataBaseName
            +"(id integer primary key, name varchar,age integer,sex varchar,phone varchar,address varchar,remark varchar)";
    QString select_max_sql = "select max(id) from "+dataBaseName;
    QString insert_sql = "insert into "+dataBaseName+"(id,name,age,sex,phone,address,remark) values(?,?,?,?,?,?,?)";
    QString update_sql = "update "+dataBaseName+"set name:=name,age:=age,sex:=sex,phone:=phone,address:=address,remark:=remark where id=:id";
    QString select_all_sql = "select id,name,age,sex,phone,address,remark from "+dataBaseName;
    QString select_id_sql = "select * from "+dataBaseName+" where id =?";
    //QString select_type_sql = "select typename from "+dataBaseName;
    QString delete_sql = "delete from "+dataBaseName+" where id =?";
    QString clear_sql = "delete from "+dataBaseName;
    QSqlDatabase db;// = QSqlDatabase::database("QSQLITE"); //建立数据库连接
    QSqlQuery* qry;
public:
    employeeDao();
    bool insert(Employee e);            //出入数据
    QVector<Employee> getPageList(Employee info,int page = 1,int pageSize = 10);
    bool deleteById(int id);
    bool update(Employee info);
    QVector<Employee> selectById(int id);
    //QVector<QString> getType();
};

#endif // EMPLOYEEDAO_H
