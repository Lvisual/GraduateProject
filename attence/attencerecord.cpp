#include "attencerecord.h"
#include "ui_attencerecord.h"

AttenceRecord::AttenceRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttenceRecord)
{
    ui->setupUi(this);
}

AttenceRecord::~AttenceRecord()
{
    delete ui;

}
