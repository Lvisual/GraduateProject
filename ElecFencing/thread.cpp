#include "thread.h"
#include "QDebug"
#include "moveman.h"
#include "QMessageBox"
Thread::Thread()
{
    m_man = nullptr;
}

void Thread::setItem(MoveMan*man){
    m_man = man;
    m_line = m_man->getTimer();
}

void Thread::run(){
    m_man->move(m_path);
}

void Thread::setPath(QVector<QPoint> v){
    m_path.clear();
    m_path.append(v);
}

void Thread::stop(){
    m_line->stop();
}





