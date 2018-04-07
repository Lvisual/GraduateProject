#ifndef PERSONALWEEKREPORT_H
#define PERSONALWEEKREPORT_H

#include <QWidget>

namespace Ui {
class PersonalWeekReport;
}

class PersonalWeekReport : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalWeekReport(QWidget *parent = 0);
    ~PersonalWeekReport();

private:
    Ui::PersonalWeekReport *ui;
};

#endif // PERSONALWEEKREPORT_H
