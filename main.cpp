#include "main_widget.h"
#include <QApplication>
#include "style.h"
#include "ElecFencing/myxml.h"
#include "RouteManage/indoormanage.h"
#include"label/labeldao.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Style::setStyle(":/new/style.qss");
     main_widget main;
     main.show();

  return a.exec();
}

