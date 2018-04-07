#ifndef BASETYPEWIDGET_H
#define BASETYPEWIDGET_H

#include <QWidget>
#include "basetypdemodel.h"
#include "basetypedao.h"
#include <QTableView>
#include "QPushButton"
#include "basetypeform.h"
class baseTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit baseTypeWidget(QWidget *parent = 0);
    void setupModel();
signals:

public slots:
    void addWin();
    void addBaseTypeInfo(baseTypeInfo&info);
    void deleteBaseType();
    void freshBaseType();
private:
    baseTypeModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_freshBtn;
    QPushButton *m_findBtn;
    baseTypeForm *m_addForm;
    baseTypeDao m_typeDao;

};

#endif // BASETYPEWIDGET_H
