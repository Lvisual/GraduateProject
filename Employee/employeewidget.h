#ifndef EMPLOYEEWIDGET_H
#define EMPLOYEEWIDGET_H

#include <QWidget>
#include "employeedao.h"
#include "employeemodel.h"
#include "addemployeeform.h"
#include "selectform.h"
#include <QTableView>
#include <QPushButton>
class employeeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit employeeWidget(QWidget *parent = 0);
    void setupModel();
signals:

public slots:
    void addWin();
    void selectWin();
    void addEmployee(Employee&info);
    void deleteEmployee();
    void freshEmployee();
    void selectEmployee(int id);
private:
    employeeModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_freshBtn;
    QPushButton *m_findBtn;

    QPushButton *nextPage;
    QPushButton *prePage;
    QPushButton *firstPage;
    QPushButton *lastPage;

    addEmployeeForm *m_addForm;
    selectForm *m_selectForm;
    employeeDao m_employeeDao;

    QWidget *widget_8;
};

#endif // EMPLOYEEWIDGET_H
