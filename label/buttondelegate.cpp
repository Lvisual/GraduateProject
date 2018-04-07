
#include "buttondelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QDialog>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QColor>
#include "labeldetail.h"
ButtonDelegate::ButtonDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void ButtonDelegate::paint(QPainter *painter,  const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPalette palette=QPalette(Qt::white);
    //画刷的活动颜色组
    palette.setBrush(QPalette::ButtonText,QColor(30,144,255));//按钮文字颜色
    palette.setBrush(QPalette::Button,Qt::white);
    QStyleOptionButton* button = m_btns.value(index);
    if (!button) {
        button = new QStyleOptionButton();
        button->palette =palette;
        button->rect = option.rect.adjusted(4, 4, -4, -4);
        button->text = QString::fromLocal8Bit("查看详情");
        button->state |= QStyle::State_Enabled;
        button->iconSize = QSize(16,16);
        button->icon = QIcon(":/new/images/detail.png");
        (const_cast<ButtonDelegate *>(this))->m_btns.insert(index, button);
    }
    painter->save();


    if (option.state & QStyle::State_Selected) {
        //painter->fillRect(option.rect, option.palette.highlight());
         painter->fillRect(option.rect,QColor(120,170,220));

    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, button, painter);
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent* e =(QMouseEvent*)event;

        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && m_btns.contains(index)) {
            m_btns.value(index)->state |= QStyle::State_Sunken;
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (option.rect.adjusted(4, 4, -4, -4).contains(e->x(), e->y()) && m_btns.contains(index)) {
            m_btns.value(index)->state &= (~QStyle::State_Sunken);  
            Label query;
            QVector<Label> infos = m_labelDao.getPageList(query);
            int employeeId = infos.at(index.row()).employeeId();
            labelDetail *labelwin = new labelDetail(employeeId);
            labelwin->show();
        }
    }
}
