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

include_directories("ThrusterSettings")
include_directories("CommunicationSettings")
include_directories("ControlSettings")
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
    add_subdirectory(Utilitis/hidapi)
else()
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
    include_directories(${HIDAPI_INCLUDE_DIR})
endif()

set(PROJECT_SOURCES
        main.cpp
        ControlSettings/ControlBase.cpp
        ControlSettings/Control.cpp
        ControlSettings/Joystick.cpp
        ControlSettings/Keyboard.cpp
        ControlSettings/Mouse3d.cpp
        ControlSettings/ControlWindow.cpp
        KX_Pult/configdata.cpp
        KX_Pult/kx_protocol.cpp
        KX_Pult/qkx_coeffs.cpp
        KX_Pult/qpiconfig.cpp
        PicFrame/picframe.cpp
        ThrusterSettings/ThrusterWindow.cpp
        ThrusterSettings/Thruster.cpp
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
        CommunicationSettings/SerialClient.cpp
        CommunicationSettings/UdpClient.cpp
        mainwindow.cpp

        ControlSettings/ControlBase.h
        ControlSettings/Control.h
        ControlSettings/Joystick.h
        ControlSettings/Keyboard.h
        ControlSettings/Mouse3d.h
        ControlSettings/ControlWindow.h
        KX_Pult/configdata.h
        KX_Pult/kx_protocol.h
        KX_Pult/qkx_coeffs.h
        KX_Pult/qpiconfig.h
        PicFrame/picframe.h
        UI_Tests/serverdata_test.h
        UV/ibasicdata.h
        UV/icontroldata.h
        UV/iserverdata.h
        UV/ituningdata.h
        UV/iuserinterfacedata.h
        UV/uv_controlcontour.h
        UV/uv_device.h
        UV/uv_state.h
        ThrusterSettings/ThrusterWindow.h
        ThrusterSettings/Thruster.h
        UV/uv_thruster.h
        VehicleWizard/vehiclewizard.h
        mainwindow.h
        CommunicationSettings/SerialClient.h
        CommunicationSettings/UdpClient.h

        PicFrame/picframe.ui
        ThrusterSettings/ThrusterWindow.ui
        ThrusterSettings/Thruster.ui
        ControlSettings/ControlWindow.ui
        VehicleWizard/vehiclewizard.ui
        mainwindow.ui
        )

set(QRC_FILES
        images.qrc
        vehicles.qrc)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        CommunicationSettings
        ControlSettings
        ThrusterSettings
        VehicleWizard
        PicFrame
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_FILES}) # Qt 6.1 - Note: This command is in technology preview and may change in future releases.
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${QRC_FILES})
endif ()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Utilitis/hidapi)
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
