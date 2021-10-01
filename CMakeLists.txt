cmake_minimum_required(VERSION 3.5)

project(PoolsideGUI VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#---------- C++ version -----------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#----------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

SET(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_PREFIX_PATH "$ENV{QTDIR}")

if (MSVC)
    message(FATAL_ERROR "The progect cmake no build in MSVC!")
else()
    add_compile_options(-Wall -Wextra)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED)#COMPONENTS Core Gui Widgets SerialPort Network Test REQUIRED)

if(${QT_VERSION_MAJOR} EQUAL 6)
    if(${QT_VERSION_MINOR} LESS 2)
        message(FATAL_ERROR "In versions 6.0 to 6.1, the SerialPort library was removed")
    elseif(${QT_VERSION_MINOR} EQUAL 2)
        message(FATAL_ERROR "The project will not be assembled due to an internal problem in the Qt 6.2.0 beta2 version  -  https://bugreports.qt.io/browse/QTBUG-95391")
    endif()
endif()

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets SerialPort Network Test REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/VehicleSettings")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/ThrusterSettings")
include_directories("${PROJECT_SOURCE_DIR}/SettingsWindow/CommunicationSettings")
include_directories("${PROJECT_SOURCE_DIR}/VehicleWizard")
include_directories("${PROJECT_SOURCE_DIR}/PicFrame")

#SFML
if(WIN32)
    add_subdirectory(SFML/SFML)
else()
    set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/")
    find_package(SFML 2.4 REQUIRED graphics window system audio)
    include_directories(${SFML_INCLUDE_DIR})
endif()

#HIDAPI
if(WIN32)
    add_subdirectory(hidapi)
else()
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
    include_directories(${HIDAPI_INCLUDE_DIR})
endif()

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
        SettingsWindow/SetConfiguration/setconfiguration.cpp
        SettingsWindow/SetConfiguration/dialogcommit.cpp
        SettingsWindow/SetConfiguration/mypushbutton.cpp
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
        SettingsWindow/SetConfiguration/setconfiguration.h
        SettingsWindow/SetConfiguration/dialogcommit.h
        SettingsWindow/SetConfiguration/mypushbutton.h
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
        serial_client.h
        udp_client.h
        PicFrame/picframe.ui
        SettingsWindow/CommunicationSettings/communicationsettings.ui
        SettingsWindow/CommunicationSettings/serial_settings.ui
        SettingsWindow/CommunicationSettings/udp_settings.ui
        SettingsWindow/ThrusterSettings/thrustersettings.ui
        SettingsWindow/VehicleSettings/vehiclesettings.ui
        SettingsWindow/SetConfiguration/setconfiguration.ui
        SettingsWindow/SetConfiguration/dialogcommit.ui
        VehicleWizard/vehiclewizard.ui
        mainwindow.ui
        SettingsWindow/settingswindow.ui
        )

set(QRC_FILES
        images.qrc
        vehicles.qrc)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        SettingsWindow
        SettingsWindow/VehicleSettings
        SettingsWindow/ThrusterSettings
        SettingsWindow/CommunicationSettings
        SettingsWindow/SetConfiguration
        VehicleWizard
        PicFrame
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_FILES}) # Qt 6.1 - Note: This command is in technology preview and may change in future releases.
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_FILES})
endif ()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} hidapi)
else()
    target_link_libraries(${PROJECT_NAME} hidapi-libusb)
endif()

target_link_libraries(${PROJECT_NAME}
        sfml-graphics sfml-window sfml-system
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
