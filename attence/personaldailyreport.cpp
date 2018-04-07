#include "personaldailyreport.h"
#include "ui_personaldailyreport.h"

PersonalDailyReport::PersonalDailyReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalDailyReport)
{
    ui->setupUi(this);
}

PersonalDailyReport::~PersonalDailyReport()
{
    delete ui;
}
