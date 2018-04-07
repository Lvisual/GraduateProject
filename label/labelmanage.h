#ifndef LABELMANAGE_H
#define LABELMANAGE_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QString>
#include "labelmodel.h"
#include "labeldao.h"
#include "selectLabelForm.h"
#include "addlabelform.h"
#include "buttondelegate.h"

namespace Ui {
class labelmanage;
}

class labelmanage : public QWidget
{
    Q_OBJECT

public:
    explicit labelmanage(QWidget *parent = 0);
    ~labelmanage();
    void setupModel();
signals:

public slots:
    void addWin();
    void selectWin();
    void addLabel(Label&info);
    void deleteLabel();
    void freshLabel();
    void selectLabel(int id);
private:
    LabelModel *m_model;
    QTableView *m_tableView;
    QPushButton *m_addBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_freshBtn;
    QPushButton *m_findBtn;

    QPushButton *nextPage;
    QPushButton *prePage;
    QPushButton *firstPage;
    QPushButton *lastPage;

    addLabelForm *m_addForm;
    selectLabelForm *m_selectLabelForm;
    labelDao m_labelDao;
    ButtonDelegate *m_delegateBtn;

    QWidget *widget_9;
private:
    Ui::labelmanage *ui;

};

#endif // LABELMANAGE_H
