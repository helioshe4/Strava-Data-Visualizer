QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credentialsdialog.cpp \
    main.cpp \
    stravachart.cpp \
    $$PWD/../src/api.cpp

HEADERS += \
    credentialsdialog.h \
    customchartview.h \
    stravachart.h \
    $$PWD/../include/api.h \
    $$PWD/../include/workoutdatapoint.h \
    $$PWD/../include/json.h

FORMS += \
    stravachart.ui

LIBS += -lcurl

#INCLUDEPATH += $$PWD/../include/json.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
