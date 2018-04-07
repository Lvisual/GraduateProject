#ifndef BASETYPEDAO_H
#define BASETYPEDAO_H

#include <QObject>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include "basetypdemodel.h"
class baseTypeInfo;

class baseTypeDao : public QObject
{
    Q_OBJECT
    const QString dataBaseName = "baseStationTypeTable";

    QString create_sql = "create table if not exists "+dataBaseName
            +"(id integer primary key, typename varchar,remark varchar)";
    QString select_max_sql = "select max(id) from "+dataBaseName;
    QString insert_sql = "insert into "+dataBaseName+"(id,typename,remark) values(?,?,?)";
    QString update_sql = "update "+dataBaseName+"set typename:=typename, remark:=remark where id=:id";
    QString select_all_sql = "select id,typename,remark from "+dataBaseName;
    QString select_type_sql = "select typename from "+dataBaseName;
    QString delete_sql = "delete from "+dataBaseName+" where id =?";
    QString clear_sql = "delete from "+dataBaseName;
    QSqlDatabase db;// = QSqlDatabase::database("QSQLITE"); //建立数据库连接
    QSqlQuery* qry;
public:
    baseTypeDao();
    bool insert(baseTypeInfo b);            //出入数据
    QVector<baseTypeInfo> getPageList(baseTypeInfo info,int page = 1,int pageSize = 10);
    bool deleteById(int id);
    bool update(baseTypeInfo info);
    QVector<QString> getType();
};

#endif // BASETYPEDAO_H
