#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include "Employee/employeedao.h"
#include "labeldao.h"
class ButtonDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ButtonDelegate(QObject *parent = 0);
    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void emplyeeId(int);
public slots:

private:
    QMap<QModelIndex, QStyleOptionButton*> m_btns;
    labelDao m_labelDao;
};

#endif // BUTTONDELEGATE_H

