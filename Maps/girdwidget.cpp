#include "girdwidget.h"
#include "ui_girdwidget.h"
#include <QtGui/QPainter>


GirdWidget::GirdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GirdWidget)
{
    ui->setupUi(this);
    h1=new QHBoxLayout;
    this->setLayout(h1);
    widget1=new QWidget();
    widget1->installEventFilter(this);
    h1->addWidget(widget1);
  //  paintOnWidget(widget1);
}

GirdWidget::~GirdWidget()
{
    delete ui;
}

bool GirdWidget::eventFilter(QObject *watched, QEvent *e) {
    if (watched == widget1) {
        if (e->type() == QEvent::Paint) {
            paintOnWidget(widget1);
            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}
void GirdWidget::paintOnWidget(QWidget *w) {
    QPainter painter(w);

    QFontMetrics metrics = painter.fontMetrics();
    int textHeight = metrics.ascent() + metrics.descent();

    int leftWidth = metrics.width(tr("9000")) + 5;
    int rightWidth = metrics.width(tr("(日)"));
    int width = w->size().width() - leftWidth - rightWidth;
    int height = w->size().height() - 3 * textHeight;

    // 绘制外框
    painter.drawRect(0, 0, w->size().width() -1, w->size().height() - 1);
    //　移动坐标系
    //painter.translate(inset * 2, ui->yearWidget->size().height() - inset);
    painter.translate(leftWidth, 1.75 * textHeight + height);

    int totalCount = 9000; // 默认每年收入9000件衣服
    int count = 12 ;        // 分成10成
//    float deltaX = width / 12.0f;         // x坐标上每分的宽度
//    float deltaY = (float)height / count; // y坐标上每分的宽度
    int deltaX = 50;
    int deltaY = 50;


    // 画横坐标
    painter.drawLine(0, 0, width, 0);
    for (int i = 1; i <= 12; ++i) {
        QString month = tr("%1月").arg(i);
        int stringWidth = metrics.width(month);

        // 绘制坐标刻度
        painter.drawLine(deltaX * i, 0, deltaX * i, 4);

        // 绘制坐标处的月
        int monthX = deltaX * (i - 1) + ((deltaX - stringWidth) / 2);
        painter.drawText(monthX, textHeight, month);
    }

    // 画纵坐标
    painter.drawLine(0, 0, 0, -height);
    painter.drawText(-metrics.width(tr("(件)")),
                     -(deltaY * count + textHeight / 2 + metrics.descent()),
                     tr("(件)"));
    for (int i = 1; i <= count; ++i) {
        QString value = QString("%1").arg(i * totalCount / count);
        int stringWidth = metrics.width(value);

        // 绘制坐标刻度
        painter.drawLine(-4, -i * deltaY, 0, -i * deltaY);

        // 绘制坐标值
        //painter.drawText(-stringWidth - 4, -i * deltaY + stringHeight / 2, value);
        painter.drawText(-stringWidth - 4, -(deltaY * i + textHeight / 2 - metrics.ascent()), value);
    }

}

