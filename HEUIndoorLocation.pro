#-------------------------------------------------
#
# Project created by QtCreator 2017-05-16T14:48:12
#
#-------------------------------------------------

QT       += core gui sql
QT       += core gui xml
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HEUIndoorLocation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    titlewidget.cpp \
    tool_button.cpp \
    push_button.cpp \
    main_widget.cpp \
    util.cpp \
    contentwidget.cpp \
    warningwidget.cpp \
    basestation/basestationdao.cpp \
    basestation/basemodel.cpp \
    basestation/jzwidget.cpp \
    attence/kqwidget.cpp \
    camera/bqwidget.cpp \
    label/truebqwidget.cpp \
    Maps/mapwidget.cpp \
    basestation/basestationform.cpp \
    style.cpp \
    basestation/formtitle.cpp \
    Maps/brushandcolor.cpp \
    Maps/drawobj.cpp \
    Maps/drawscene.cpp \
    Maps/drawtool.cpp \
    Maps/sizehandle.cpp \
    Maps/mapdrawing.cpp \
    LocateMonitor/locatemonitor.cpp \
    LocateMonitor/indexwidget.cpp \
    LocateMonitor/lomowidget.cpp \
    LocateMonitor/lomomainwidget.cpp \
    LocateMonitor/lomoview.cpp \
    mainmenu.cpp \
    logs.cpp \
    filterset.cpp \
    Maps/dijkstrafindpath.cpp \
    Maps/moveitem.cpp \
    Maps/myfile.cpp \
    Maps/route.cpp \
    DaoHang/centralwidget.cpp \
    DaoHang/message.cpp \
    DaoHang/navdelegate.cpp \
    DaoHang/naviview.cpp \
    DaoHang/navmodel.cpp \
    DaoHang/dhpushbutton.cpp \
    ElecFencing/elecfencewidget.cpp \
    Maps/newroute.cpp \
    ElecFencing/position.cpp \
    Maps/userpath.cpp \
    camera/cameralinkage.cpp \
    camera/cameramanage.cpp \
    Maps/mapsmanage.cpp \
    Maps/mapsinformation.cpp \
    label/labelmanage.cpp \
    label/labelinformation.cpp \
    ElecFencing/moveman.cpp \
    basestation/basetypewidget.cpp \
    basestation/basetypdemodel.cpp \
    basestation/basetypedao.cpp \
    basestation/basetypeform.cpp \
    RouteManage/routemanage.cpp \
    ElecFencing/thread.cpp \
    ccustommessagebox.cpp \
    ElecFencing/historychoice.cpp \
    Employee/employeedao.cpp \
    Employee/employeemodel.cpp \
    Employee/employeewidget.cpp \
    Employee/addemployeeform.cpp \
    Employee/selectform.cpp \
    ElecFencing/monitorroute.cpp \
    Maps/girdwidget.cpp \
    attence/signinwidget.cpp \
    attence/personaldailyreport.cpp \
    attence/personalweekreport.cpp \
    attence/attencerecord.cpp \
    ElecFencing/myxml.cpp \
    label/addlabelform.cpp \
    label/labeldao.cpp \
    label/labelmodel.cpp \
    label/selectlabelform.cpp \
    label/buttondelegate.cpp \
    label/labeldetail.cpp \
    attence/signindao.cpp \
    attence/signinmodel.cpp \
    attence/signinreport.cpp \
    ElecFencing/elecfencingview.cpp \
    camera/static3dwidget.cpp \
    camera/tglwidget.cpp \
    camera/display3dwidget.cpp \
    camera/glwidget.cpp \
    DataAnalysis/heatmap.cpp \
    DataAnalysis/histogram.cpp \
    DataAnalysis/stat.cpp \
    DataAnalysis/statmodel.cpp \
    DataAnalysis/widget_heatmap.cpp \
    DataAnalysis/widget_histogram.cpp \
    RouteManage/astar.cpp \
    RouteManage/BowyerWatson.cpp \
    RouteManage/judge.cpp \
    RouteManage/Line.cpp \
    RouteManage/Point.cpp \
    RouteManage/bwposition.cpp \
    RouteManage/bwfile.cpp \
    RouteManage/Triangle.cpp \
    RouteManage/indoormanage.cpp \
    RouteManage/mapscene.cpp \
    RouteManage/indoorscene.cpp \
    RouteManage/targetitem.cpp \
    basestation/selectbaseform.cpp

HEADERS  += mainwindow.h \
    titlewidget.h \
    tool_button.h \
    push_button.h \
    main_widget.h \
    util.h \
    contentwidget.h \
    warningwidget.h \
    basestation/basestationdao.h \
    basestation/basemodel.h \
    basestation/jzwidget.h \
    attence/kqwidget.h \
    camera/bqwidget.h \
    label/truebqwidget.h \
    Maps/mapwidget.h \
    basestation/basestationform.h \
    style.h \
    basestation/formtitle.h \
    Maps/brushandcolor.h \
    Maps/drawobj.h \
    Maps/drawscene.h \
    Maps/drawtool.h \
    Maps/sizehandle.h \
    Maps/mapdrawing.h \
    LocateMonitor/locatemonitor.h \
    LocateMonitor/indexwidget.h \
    LocateMonitor/lomowidget.h \
    LocateMonitor/lomomainwidget.h \
    LocateMonitor/lomoview.h \
    mainmenu.h \
    logs.h \
    filterset.h \
    Maps/dijkstrafindpath.h \
    Maps/moveitem.h \
    Maps/myfile.h \
    Maps/route.h \
    DaoHang/centralwidget.h \
    DaoHang/colordefines.h \
    DaoHang/message.h \
    DaoHang/navdelegate.h \
    DaoHang/naviview.h \
    DaoHang/navmodel.h \
    DaoHang/dhpushbutton.h \
    ElecFencing/elecfencewidget.h \
    Maps/newroute.h \
    ElecFencing/position.h \
    Maps/userpath.h \
    camera/cameralinkage.h \
    camera/cameramanage.h \
    Maps/mapsmanage.h \
    Maps/mapsinformation.h \
    label/labelmanage.h \
    label/labelinformation.h \
    ElecFencing/moveman.h \
    basestation/basetypewidget.h \
    basestation/basetypdemodel.h \
    basestation/basetypedao.h \
    basestation/basetypeform.h \
    RouteManage/routemanage.h \
    ElecFencing/thread.h \
    ccustommessagebox.h \
    ElecFencing/historychoice.h \
    Employee/employeedao.h \
    Employee/employeemodel.h \
    Employee/employeewidget.h \
    Employee/addemployeeform.h \
    Employee/selectform.h \
    ElecFencing/monitorroute.h \
    Maps/girdwidget.h \
    attence/signinwidget.h \
    attence/personaldailyreport.h \
    attence/personalweekreport.h \
    attence/attencerecord.h \
    ElecFencing/myxml.h \
    label/addlabelform.h \
    label/labeldao.h \
    label/labelmodel.h \
    label/selectlabelform.h \
    label/buttondelegate.h \
    label/labeldetail.h \
    attence/signindao.h \
    attence/signinmodel.h \
    attence/signinreport.h \
    ElecFencing/elecfencingview.h \
    camera/static3dwidget.h \
    camera/tglwidget.h \
    camera/display3dwidget.h \
    camera/glwidget.h \
    DataAnalysis/heatmap.h \
    DataAnalysis/histogram.h \
    DataAnalysis/stat.h \
    DataAnalysis/statmodel.h \
    DataAnalysis/widget_heatmap.h \
    DataAnalysis/widget_histogram.h \
    RouteManage/astar.h \
    RouteManage/BowyerWatson.h \
    RouteManage/judge.h \
    RouteManage/Line.h \
    RouteManage/Point.h \
    RouteManage/bwposition.h \
    RouteManage/bwfile.h \
    RouteManage/Triangle.h \
    RouteManage/indoormanage.h \
    RouteManage/mapscene.h \
    RouteManage/indoorscene.h \
    RouteManage/targetitem.h \
    basestation/selectbaseform.h

FORMS    += mainwindow.ui \
    titlewidget.ui \
    main_widget.ui \
    contentwidget.ui \
   # jzwidget.ui \
   # bqwidget.ui \
   # kqwidget.ui \
   # truebqwidget.ui \
    basestation/jzwidget.ui \
    attence/kqwidget.ui \
    camera/bqwidget.ui \
    label/truebqwidget.ui \
    Maps/mapwidget.ui \
    basestation/basestationform.ui \
    Maps/mapdrawing.ui \
    LocateMonitor/locatemonitor.ui \
    LocateMonitor/indexwidget.ui \
    LocateMonitor/lomowidget.ui \
    LocateMonitor/lomomainwidget.ui \
    logs.ui \
    filterset.ui \
    ElecFencing/elecfencewidget.ui \
    camera/cameralinkage.ui \
    camera/cameramanage.ui \
    Maps/mapsmanage.ui \
    Maps/mapsinformation.ui \
    label/labelmanage.ui \
    label/labelinformation.ui \
    RouteManage/routemanage.ui \
    Employee/form.ui \
    Maps/girdwidget.ui \
    attence/signinwidget.ui \
    attence/personaldailyreport.ui \
    attence/personalweekreport.ui \
    attence/attencerecord.ui \
    attence/signinreport.ui

RESOURCES += \
    image.qrc

CONFIG += qwt


INCLUDEPATH += C:\Qt\Qt5.8.0\5.8\mingw53_32\include\Qwt
LIBS += -L"C:\Qt\Qt5.8.0\5.8\mingw53_32\lib" -lqwtd

#LIBS += -L"D:\GLC_lib-master\src\lib" -lGLC_lib3
#INCLUDEPATH += "D:\GLC_lib-master\src\lib"
#LIBS += -lopengl32
LIBS += -L"D:\GLC_lib-master\src\lib" -lGLC_lib3
INCLUDEPATH += "D:\GLC_lib-master\src\lib"
LIBS += -lopengl32
