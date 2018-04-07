#include "basetypedao.h"

baseTypeDao::baseTypeDao(): QObject()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sql.db");
    if( !db.open()) {
        qDebug() << QString::fromLocal8Bit("can not connect");
    } else {
        qDebug() << "connect success";
        this->qry = new QSqlQuery(db);
        // create table
        qDebug() << create_sql <<endl;
        if(qry->exec(create_sql)){
            qDebug() << QString::fromLocal8Bit("create BaseStationTypeTable success");
        }else{
            qDebug() << QString::fromLocal8Bit("create BaseStationTypeTable fail");
        }
    }

}
//向数据库中插入记录
bool baseTypeDao::insert(baseTypeInfo b) {

    //QSqlDatabase db = QSqlDatabase::database("QSQLITE"); //建立数据库连接

    int max_id = 0;
    this->qry = new QSqlQuery(db);
    qry->prepare(select_max_sql);
    if(!qry->exec())
    {
        qDebug()<<"max id error";
        qDebug()<<qry->lastError();
        return false;
    }
    else
    {
        while(qry->next())
        {
            max_id = qry->value(0).toInt();
            qDebug()<<QString("max id:%1").arg(max_id);
        }
    }
    qry->prepare(this->insert_sql);
    qry->addBindValue(max_id+1);
    qry->addBindValue(b.getTypeName());
    qry->addBindValue(b.getTypeRemark());
    if( !qry->exec() ){
     qDebug()<<"insert error";
     return false;
    }else
       return true;
}

 QVector<baseTypeInfo> baseTypeDao::getPageList(baseTypeInfo info,int page,int pageSize){
     QVector<baseTypeInfo> list;
     QString sql = this->select_all_sql+" where 1=1";
      this->qry = new QSqlQuery(db);
     qry->prepare(sql);
     if(!qry->exec())
     {
        qDebug()<<qry->lastError();
     }
     else
     {
         while(qry->next())
         {
             baseTypeInfo info;
             info.setBaseTypeId(qry->value(0).toString());
             info.setBaseTypeName(qry->value(1).toString());
             info.setBaseTypeRemark(qry->value(2).toString());
             list.push_back(info);
         }
     }
     return list;
 }

bool baseTypeDao::deleteById(int id){
   this->qry = new QSqlQuery(db);
   qry->prepare(this->delete_sql);
   qry->addBindValue(id);
   if(qry->exec()){
       return true;
   }else{
       qDebug()<<qry->lastError()<<endl;
       return false;
   }

}
bool baseTypeDao::update(baseTypeInfo info){
    this->qry = new QSqlQuery(db);
    qry->prepare(this->update_sql);
    qry->bindValue(":typename",info.getTypeName());
    qry->bindValue(":remark",info.getTypeRemark());
    qry->bindValue(":id",info.getTypeId());
    if(qry->exec()){
        return true;
    }else{
        qDebug()<<qry->lastError()<<endl;
        return false;
    }
}

QVector<QString> baseTypeDao::getType(){
    QVector<QString> v;
    this->qry = new QSqlQuery(db);
    qry->prepare(this->select_type_sql);
    if(!qry->exec())
    {
    qDebug()<<qry->lastError();
    }
    else{
    while(qry->next())
    {
    v.push_back(qry->value(0).toString());
    }
    }
    return v;
}



