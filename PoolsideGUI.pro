QT       += core gui widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SettingsWindow/ThrusterSettings/thrustersettings.cpp \
    VehicleWizard/vehiclewizard.cpp \
    UV/ibasicdata.cpp \
    UV/iserverdata.cpp \
    UV/uv_device.cpp \
    UV/uv_stabilization.cpp \
    UV/uv_state.cpp \
    main.cpp \
    com_server.cpp \
    mainwindow.cpp \
    SettingsWindow/settingswindow.cpp \
    rovmodewidget.cpp

HEADERS += \
    UV/ibasicdata.h \
    UV/iserverdata.h \
    UV/uv_device.h \
    UV/uv_stabilization.h \
    UV/uv_state.h \
    SettingsWindow/ThrusterSettings/thrustersettings.h \
    VehicleWizard/vehiclewizard.h \
    mainwindow.h \
    com_server.h \
    SettingsWindow/settingswindow.h \
    rovmodewidget.h

FORMS += \
    SettingsWindow/ThrusterSettings/thrustersettings.ui \
    VehicleWizard/vehiclewizard.ui \
    mainwindow.ui \
    SettingsWindow/settingswindow.ui \
    rovmodewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix {
    DEFINES += OS=\\\"unix\\\"
    message("Unix build")
    #INCLUDEPATH += $$PWD/SFML-linux/include
    #DEPENDPATH += $$PWD/SFML-linux/include
    #LIBS += -L$$PWD/SFML-linux/lib
    #CONFIG(release, debug|release): LIBS += -lsfml-window
    #CONFIG(debug, debug|release): LIBS += -lsfml-window
}

win32 {
    DEFINES += OS=\\\"win32\\\"
    message("Windows build")
    #INCLUDEPATH += $$PWD/SFML-win32/include
    #DEPENDPATH += $$PWD/SFML-win32/include
    #LIBS += -L$$PWD/SFML-win32/lib
    #CONFIG(release, debug|release): LIBS += -lsfml-window
    #CONFIG(debug, debug|release): LIBS += -lsfml-window-d
}
