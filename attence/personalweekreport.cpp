#include "personalweekreport.h"
#include "ui_personalweekreport.h"

PersonalWeekReport::PersonalWeekReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalWeekReport)
{
    ui->setupUi(this);
}

PersonalWeekReport::~PersonalWeekReport()
{
    delete ui;
}
