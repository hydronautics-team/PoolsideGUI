cmake_minimum_required(VERSION 3.5)
project(PoolsideGUI VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

SET(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")
add_compile_options(-Wall -Wextra)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets SerialPort Network Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets SerialPort Network Test REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/VehicleSettings")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/ThrusterSettings")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/CommunicationSettings")
include_directories("${PROJECT_SOURCE_DIR}/VehicleWizard")
include_directories("${PROJECT_SOURCE_DIR}/PicFrame")

#SFML
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")
find_package(SFML 2.4 REQUIRED COMPONENTS
        graphics window system audio)
include_directories(${SFML_INCLUDE_DIR})
#HIDAPI
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
#include_directories(/usr/local/include/hidapi/)
include_directories(${HIDAPI_INCLUDE_DIR})

set(PROJECT_SOURCES
        main.cpp
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
        mainwindow.cpp
        SettingsWindow/settingswindow.cpp
        rovmodewidget.cpp
        serial_client.cpp
        udp_client.cpp
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

set(CMAKE_AUTOUIC_SEARCH_PATHS
        SettingsWindow
        SettingsWindow/VehicleSettings
        SettingsWindow/ThrusterSettings
        SettingsWindow/CommunicationSettings
        VehicleWizard
        PicFrame
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            )
else ()
    if (ANDROID)
        add_library(${PROJECT_NAME} SHARED
                ${PROJECT_SOURCES}
                )
    else ()
        add_executable(${PROJECT_NAME}
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system
        hidapi-libusb
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::SerialPort
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Test)

install(FILES
        settings.ini
        DESTINATION ./)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)