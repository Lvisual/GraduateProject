#include "employeedao.h"

employeeDao::employeeDao(): QObject()
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
            qDebug() << QString::fromLocal8Bit("create EmployeeTable success");
        }else{
            qDebug() << QString::fromLocal8Bit("create EmployeeTable fail");
        }
    }

}
//向数据库中插入记录
bool employeeDao::insert(Employee b) {

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
    qry->addBindValue(b.name());
    qry->addBindValue(b.age());
    qry->addBindValue(b.sex());
    qry->addBindValue(b.phone());
    qry->addBindValue(b.address());
    qry->addBindValue(b.remark());
    if( !qry->exec() ){
     qDebug()<<"insert error";
     return false;
    }else
       return true;
}

 QVector<Employee> employeeDao::getPageList(Employee info,int page,int pageSize){
     QVector<Employee> list;
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
             Employee info;
             info.setId(qry->value(0).toInt());
             info.setName(qry->value(1).toString());
             info.setAge(qry->value(2).toInt());
             info.setSex(qry->value(3).toString());
             info.setPhone(qry->value(4).toString());
             info.setAddress(qry->value(5).toString());
             info.setRemark(qry->value(6).toString());
             list.push_back(info);
         }
     }
     return list;
 }

bool employeeDao::deleteById(int id){
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

bool employeeDao::update(Employee info){
    this->qry = new QSqlQuery(db);
    qry->prepare(this->update_sql);
    qry->bindValue(":name",info.name());
    qry->bindValue(":age",info.age());
    qry->bindValue(":sex",info.sex());
    qry->bindValue(":phone",info.phone());
    qry->bindValue(":address",info.address());
    qry->bindValue(":remark",info.remark());
    qry->bindValue(":id",info.id());
    if(qry->exec()){
        return true;
    }else{
        qDebug()<<qry->lastError()<<endl;
        return false;
    }
}

QVector<Employee> employeeDao::selectById(int id){
    QVector<Employee>v;
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
            Employee info;
            info.setId(qry->value(0).toInt());
            info.setName(qry->value(1).toString());
            info.setAge(qry->value(2).toInt());
            info.setSex(qry->value(3).toString());
            info.setPhone(qry->value(4).toString());
            info.setAddress(qry->value(5).toString());
            info.setRemark(qry->value(6).toString());
            v.push_back(info);
        }
    }
    return v;
}



/*
QVector<QString> employeeDao::getType(){
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
*/
