cmake_minimum_required(VERSION 3.19)
project(PoolsideGUI)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets SerialPort Network Test)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::SerialPort Qt5::Network Qt5::Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCES
        Drivers/controlbase.cpp
        Drivers/joystick.cpp
        Drivers/keyboard.cpp
        Drivers/mouse_3d.cpp
        KX_Pult/configdata.cpp
        KX_Pult/kx_protocol.cpp
        KX_Pult/qkx_coeffs.cpp
        KX_Pult/qpiconfig.cpp
        PicFrame/picframe.cpp
        SettingsWindow/CommunicationSettings/communicationsettings.cpp
        SettingsWindow/CommunicationSettings/serial_settings.cpp
        SettingsWindow/CommunicationSettings/udp_settings.cpp
        SettingsWindow/ThrusterSettings/thrustersettings.cpp
        SettingsWindow/VehicleSettings/vehiclesettings.cpp
        UI_Tests/serverdata_test.cpp
        UV/icontroldata.cpp
        UV/ituningdata.cpp
        UV/iuserinterfacedata.cpp
        UV/uv_controlcontour.cpp
        UV/uv_thruster.cpp
        VehicleWizard/vehiclewizard.cpp
        UV/ibasicdata.cpp
        UV/iserverdata.cpp
        UV/uv_device.cpp
        UV/uv_state.cpp
        main.cpp
        mainwindow.cpp
        SettingsWindow/settingswindow.cpp
        rovmodewidget.cpp
        serial_client.cpp
        udp_client.cpp
        )

set(HEADERS
        Drivers/controlbase.h
        Drivers/joystick.h
        Drivers/keyboard.h
        Drivers/mouse_3d.h
        KX_Pult/configdata.h
        KX_Pult/kx_protocol.h
        KX_Pult/qkx_coeffs.h
        KX_Pult/qpiconfig.h
        PicFrame/picframe.h
        SettingsWindow/CommunicationSettings/communicationsettings.h
        SettingsWindow/CommunicationSettings/serial_settings.h
        SettingsWindow/CommunicationSettings/udp_settings.h
        SettingsWindow/VehicleSettings/vehiclesettings.h
        UI_Tests/serverdata_test.h
        UV/ibasicdata.h
        UV/icontroldata.h
        UV/iserverdata.h
        UV/ituningdata.h
        UV/iuserinterfacedata.h
        UV/uv_controlcontour.h
        UV/uv_device.h
        UV/uv_state.h
        SettingsWindow/ThrusterSettings/thrustersettings.h
        UV/uv_thruster.h
        VehicleWizard/vehiclewizard.h
        mainwindow.h
        SettingsWindow/settingswindow.h
        rovmodewidget.h
        serial_client.h
        udp_client.h
        )

set(FORMS
        PicFrame/picframe.ui
        SettingsWindow/CommunicationSettings/communicationsettings.ui
        SettingsWindow/CommunicationSettings/serial_settings.ui
        SettingsWindow/CommunicationSettings/udp_settings.ui
        SettingsWindow/ThrusterSettings/thrustersettings.ui
        SettingsWindow/VehicleSettings/vehiclesettings.ui
        VehicleWizard/vehiclewizard.ui
        mainwindow.ui
        SettingsWindow/settingswindow.ui
        rovmodewidget.ui
        )

set(RESOURCES
        images.qrc
        vehicles.qrc
        )

include_directories(
        ./SettingsWindow
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

