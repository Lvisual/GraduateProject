#ifndef PERSONALDAILYREPORT_H
#define PERSONALDAILYREPORT_H

#include <QWidget>

namespace Ui {
class PersonalDailyReport;
}

class PersonalDailyReport : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalDailyReport(QWidget *parent = 0);
    ~PersonalDailyReport();

private:
    Ui::PersonalDailyReport *ui;
};

#endif // PERSONALDAILYREPORT_H
