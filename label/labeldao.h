#ifndef LABELDAO_H
#define LABELDAO_H
#include "labelmodel.h"
#include <QObject>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
class labelDao : public QObject
{
    Q_OBJECT
public:
    const QString dataBaseName = "labelTable";

    QString create_sql = "create table if not exists "+dataBaseName
            +"(id integer primary key,employeeid integer,charge varchar,state varchar,remark varchar)";
    QString select_max_sql = "select max(id) from "+dataBaseName;
    QString insert_sql = "insert into "+dataBaseName+"(id,employeeid,charge,state,remark) values(?,?,?,?,?)";
    QString update_sql = "update "+dataBaseName+"set employeeid:=employeeid,charge:=charge,state:=state,remark:=remark where id=:id";
    QString select_all_sql = "select id,employeeid,charge,state,remark from "+dataBaseName;
    QString select_id_sql = "select * from "+dataBaseName+" where id =?";
    //QString select_type_sql = "select typename from "+dataBaseName;
    QString delete_sql = "delete from "+dataBaseName+" where id =?";
    QString clear_sql = "delete from "+dataBaseName;
    QSqlDatabase db;// = QSqlDatabase::database("QSQLITE"); //建立数据库连接
    QSqlQuery* qry;
public:
    labelDao();
    bool insert(Label e);            //出入数据
    QVector<Label> getPageList(Label info,int page = 1,int pageSize = 10);
    bool deleteById(int id);
    bool update(Label info);
    QVector<Label> selectById(int id);

public slots:
};

#endif // LABELDAO_H
