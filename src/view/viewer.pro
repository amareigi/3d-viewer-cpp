QT       += core gui
QT += 3dcore 3drender 3dinput 3dextras widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../main.cpp \
    ../controller/controller.cpp \
    ../model/edge.cpp \
    ../model/figure.cpp \
    ../model/file_reader.cpp \
    ../model/model.cpp \
    ../model/model_operation_result.cpp \
    ../model/normalization_parameters.cpp \
    ../model/scene.cpp \
    ../model/three_d_point.cpp \
    ../model/vertex.cpp \
    control_widget.cpp \
    main_widget.cpp \
    scene_widget.cpp \
    settings_widget.cpp \
    status_widget.cpp \
    view.cpp

HEADERS += \
    ../model/*.h \
    ../controller/*.h \
    control_widget.h \
    main_widget.h \
    scene_widget.h \
    settings_widget.h \
    status_widget.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
