#ifndef ATTENCERECORD_H
#define ATTENCERECORD_H

#include <QWidget>

namespace Ui {
class AttenceRecord;
}

class AttenceRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AttenceRecord(QWidget *parent = 0);
    ~AttenceRecord();

private:
    Ui::AttenceRecord *ui;
};

#endif // ATTENCERECORD_H
