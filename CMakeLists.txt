cmake_minimum_required(VERSION 3.5)

project(PoolsideGUI VERSION 2.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets SerialPort REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets SerialPort Network Test REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/CommunicationSettings")
include_directories("${PROJECT_SOURCE_DIR}/ControlSettings")
include_directories("${PROJECT_SOURCE_DIR}/KX_Pult")
include_directories("${PROJECT_SOURCE_DIR}/PicFrame")
include_directories("${PROJECT_SOURCE_DIR}/StabilizationSettings")
include_directories("${PROJECT_SOURCE_DIR}/ThrusterSettings")
include_directories("${PROJECT_SOURCE_DIR}/UV")

include_directories("${PROJECT_SOURCE_DIR}")


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp

        CommunicationSettings/Connection.cpp
        CommunicationSettings/SerialClient.cpp
        CommunicationSettings/UdpClient.cpp

        ControlSettings/ControlBase.cpp
        ControlSettings/Joystick.cpp
        ControlSettings/Keyboard.cpp

        KX_Pult/configdata.cpp
        KX_Pult/kx_protocol.cpp
        KX_Pult/qkx_coeffs.cpp
        KX_Pult/qpiconfig.cpp

        PicFrame/picframe.cpp

        StabilizationSettings/StabilizationWindow.cpp

        ThrusterSettings/Thruster.cpp
        ThrusterSettings/ThrusterWindow.cpp

        UV/ibasicdata.cpp
        UV/icontroldata.cpp
        UV/iserverdata.cpp
        UV/ituningdata.cpp
        UV/iuserinterfacedata.cpp
        UV/uv_controlcontour.cpp
        UV/uv_device.cpp
        UV/uv_state.cpp
        UV/uv_thruster.cpp
)

set(QRC_FILES
        images.qrc
        vehicles.qrc
)

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
)


target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics sfml-window sfml-system
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::SerialPort
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
        PicFrame
)