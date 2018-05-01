#include "labeldao.h"
labelDao::labelDao(): QObject()
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
            qDebug() << QString::fromLocal8Bit("create LabelTable success");
        }else{
            qDebug() << QString::fromLocal8Bit("create LabelTable fail");
        }
    }

}
//向数据库中插入记录
bool labelDao::insert(Label b) {

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
    qry->addBindValue(b.labelName());
    qry->addBindValue(b.employeeId());
    qry->addBindValue(b.charge());
    qry->addBindValue(b.state());
    qry->addBindValue(b.remark());
    if( !qry->exec() ){
     qDebug()<<"insert error";
     return false;
    }else
       return true;
}

 QVector<Label> labelDao::getPageList(Label info,int page,int pageSize){
     QVector<Label> list;
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
             Label info;
             info.setLableId(qry->value(0).toInt());
             info.setLabelName(qry->value(1).toString());
             info.setEmployeeId(qry->value(2).toInt());
             info.setCharge(qry->value(3).toString());
             info.setState(qry->value(4).toString());
             info.setRemark(qry->value(5).toString());
             list.push_back(info);
         }
     }
     return list;
 }

bool labelDao::deleteById(int id){
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

bool labelDao::update(Label info){
    this->qry = new QSqlQuery(db);
    qry->prepare(this->update_sql);
    qry->bindValue(":labelName",info.labelName());
    qry->bindValue(":employeeid",info.employeeId());
    qry->bindValue(":charge",info.charge());
    qry->bindValue(":state",info.state());
    qry->bindValue(":remark",info.remark());
    qry->bindValue(":id",info.lableId());
    if(qry->exec()){
        return true;
    }else{
        qDebug()<<qry->lastError()<<endl;
        return false;
    }
}

QVector<Label> labelDao::selectById(int id){
    QVector<Label>v;
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
            Label info;
            info.setLableId(qry->value(0).toInt());
            info.setLabelName(qry->value(1).toString());
            info.setEmployeeId(qry->value(2).toInt());
            info.setCharge(qry->value(3).toString());
            info.setState(qry->value(4).toString());
            info.setRemark(qry->value(5).toString());
            v.push_back(info);
        }
    }
    return v;
}


QVector<QString> labelDao::getAllLabelName(){
    QVector<QString> v;
    this->qry = new QSqlQuery(db);
    qry->prepare(this->select_labelName_sql);
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




