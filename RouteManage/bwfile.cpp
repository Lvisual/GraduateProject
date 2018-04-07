#include "bwfile.h"
#include <QFile>
#include <QDebug>
BwFile::BwFile()
{
   m_row = 0;
}
void BwFile::readFile(QString fileName){
     QFile file(fileName);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        //QMessageBox::warning(this,"Warning","can't open",QMessageBox::Yes);
        qDebug() << "open failed";
     }
     QTextStream in(&file);//读取一行//如果读取多行
     while (!in.atEnd()) {
        m_buffer[m_row++] = in.readLine();
   }

}
void BwFile::writeFile(QString fileName){

     QString str="CSDN";
     QFile file(fileName);
     if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
     {
         qDebug() << "open failed";
        //QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);

     }
      QTextStream in(&file);
      in<<str<<"\n";//如果写多行，同上循环即可
      file.close();
}

 QString* BwFile::getBuffer(){
     return m_buffer;
 }

 int BwFile::getRow(){
     return m_row;
 }
