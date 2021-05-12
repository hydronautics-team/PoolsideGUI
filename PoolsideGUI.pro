QT       += core gui widgets serialport testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

unix {
    DEFINES += OS=\\\"unix\\\"
    LIBS += -L/usr/lib/x86_64-linux-gnu/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
    LIBS += -L/usr/local/lib -lhidapi-libusb
    message("Unix build")
}

win32 {
    DEFINES += OS=\\\"win32\\\"
    message("Windows build")
    LIBS += -lhid -lsetupapi -mwindows
    LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
}

INCLUDEPATH += $$PWD/SFML/include
DEPENDPATH += $$PWD/SFML/include

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
    Drivers/controlbase.cpp \
    Drivers/joystick.cpp \
    Drivers/keyboard.cpp \
    Drivers/mouse_3d.cpp \
    KX_Pult/configdata.cpp \
    KX_Pult/kx_protocol.cpp \
    KX_Pult/qkx_coeffs.cpp \
    KX_Pult/qpiconfig.cpp \
    PicFrame/picframe.cpp \
    SettingsWindow/CommunicationSettings/communicationsettings.cpp \
    SettingsWindow/CommunicationSettings/serial_settings.cpp \
    SettingsWindow/CommunicationSettings/udp_settings.cpp \
    SettingsWindow/ThrusterSettings/thrustersettings.cpp \
    SettingsWindow/VehicleSettings/vehiclesettings.cpp \
    UI_Tests/serverdata_test.cpp \
    UV/icontroldata.cpp \
    UV/ituningdata.cpp \
    UV/iuserinterfacedata.cpp \
    UV/uv_controlcontour.cpp \
    UV/uv_thruster.cpp \
    VehicleWizard/vehiclewizard.cpp \
    UV/ibasicdata.cpp \
    UV/iserverdata.cpp \
    UV/uv_device.cpp \
    UV/uv_state.cpp \
    main.cpp \
    mainwindow.cpp \
    SettingsWindow/settingswindow.cpp \
    rovmodewidget.cpp \
    serial_client.cpp \
    udp_client.cpp

HEADERS += \
    Drivers/controlbase.h \
    Drivers/joystick.h \
    Drivers/keyboard.h \
    Drivers/mouse_3d.h \
    KX_Pult/configdata.h \
    KX_Pult/kx_protocol.h \
    KX_Pult/qkx_coeffs.h \
    KX_Pult/qpiconfig.h \
    PicFrame/picframe.h \
    SettingsWindow/CommunicationSettings/communicationsettings.h \
    SettingsWindow/CommunicationSettings/serial_settings.h \
    SettingsWindow/CommunicationSettings/udp_settings.h \
    SettingsWindow/VehicleSettings/vehiclesettings.h \
    UI_Tests/serverdata_test.h \
    UV/ibasicdata.h \
    UV/icontroldata.h \
    UV/iserverdata.h \
    UV/ituningdata.h \
    UV/iuserinterfacedata.h \
    UV/uv_controlcontour.h \
    UV/uv_device.h \
    UV/uv_state.h \
    SettingsWindow/ThrusterSettings/thrustersettings.h \
    UV/uv_thruster.h \
    VehicleWizard/vehiclewizard.h \
    mainwindow.h \
    SettingsWindow/settingswindow.h \
    rovmodewidget.h \
    serial_client.h \
    udp_client.h

FORMS += \
    PicFrame/picframe.ui \
    SettingsWindow/CommunicationSettings/communicationsettings.ui \
    SettingsWindow/CommunicationSettings/serial_settings.ui \
    SettingsWindow/CommunicationSettings/udp_settings.ui \
    SettingsWindow/ThrusterSettings/thrustersettings.ui \
    SettingsWindow/VehicleSettings/vehiclesettings.ui \
    VehicleWizard/vehiclewizard.ui \
    mainwindow.ui \
    SettingsWindow/settingswindow.ui \
    rovmodewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    vehicles.qrc

DISTFILES += \
    KX_Pult/protocols.conf
