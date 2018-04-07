#include "signindao.h"

SignInDao::SignInDao(): QObject()
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
            qDebug() << QString::fromLocal8Bit("create SignInTable success");
        }else{
            qDebug() << QString::fromLocal8Bit("create SignInTable fail");
        }
    }

}
//向数据库中插入记录
bool SignInDao::insert(SignIn s) {

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
  //  qry->addBindValue(max_id+1);
    qry->addBindValue(s.id());
    qry->addBindValue(s.name());
    qry->addBindValue(s.agent());
    qry->addBindValue(s.signdate());
    qry->addBindValue(s.signtime());
    qry->addBindValue(s.status());
    qry->addBindValue(s.remark());
    if( !qry->exec() ){
     qDebug()<<"insert error";
     return false;
    }else
       return true;
}

 QVector<SignIn> SignInDao::getPageList(SignIn info,int page,int pageSize){
     QVector<SignIn> list;
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
             SignIn info;
             info.setId(qry->value(0).toInt());
             info.setName(qry->value(1).toString());
             info.setAgent(qry->value(2).toString());
             info.setSigndate(qry->value(3).toString());
             info.setSigntime(qry->value(4).toString());
             info.setStatus(qry->value(5).toString());
             info.setRemark(qry->value(6).toString());
             list.push_back(info);
         }
     }
     return list;
 }

bool SignInDao::deleteById(int id){
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

bool SignInDao::update(SignIn info){
    this->qry = new QSqlQuery(db);
    qry->prepare(this->update_sql);
    qry->bindValue(":name",info.name());
    qry->bindValue(":agent",info.agent());
    qry->bindValue(":signdate",info.signdate());
    qry->bindValue(":signtime",info.signtime());
    qry->bindValue(":status",info.status());
    qry->bindValue(":remark",info.remark());
    qry->bindValue(":id",info.id());
    if(qry->exec()){
        return true;
    }else{
        qDebug()<<qry->lastError()<<endl;
        return false;
    }
}

QVector<SignIn> SignInDao::selectById(int id){
    QVector<SignIn>v;
    this->qry = new QSqlQuery(db);
    qry->prepare(this->select_id_sql);
    qry->addBindValue(id);
    //qry->prepare(select_id_sql.arg(id));
    //qry->addBindValue(id);
    if(!qry->exec())
    {
       qDebug() <<"hehe";
       qDebug()<<qry->lastError();
    }
    else
    {
        while(qry->next())
        {
            SignIn info;
            info.setId(qry->value(0).toInt());
            info.setName(qry->value(1).toString());
            info.setAgent(qry->value(2).toString());
            info.setSigndate(qry->value(3).toString());
            info.setSigntime(qry->value(4).toString());
            info.setStatus(qry->value(5).toString());
            info.setRemark(qry->value(6).toString());
            v.push_back(info);
        }
    }
    return v;
}
