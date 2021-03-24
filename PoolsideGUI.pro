QT       += core gui widgets serialport testlib network gamepad

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# SFML
# WINDOWS ONLY

DEFINES += SFML_STATIC
INCLUDEPATH += $$PWD/External/SFML/include
DEPENDPATH += $$PWD/External/SFML/include
LIBS += -L$$PWD/External/SFML/lib
CONFIG(release, debug|release): LIBS += -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-window-d

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
    External/SFML/include/SFML/Audio.hpp \
    External/SFML/include/SFML/Audio/AlResource.hpp \
    External/SFML/include/SFML/Audio/Export.hpp \
    External/SFML/include/SFML/Audio/InputSoundFile.hpp \
    External/SFML/include/SFML/Audio/Listener.hpp \
    External/SFML/include/SFML/Audio/Music.hpp \
    External/SFML/include/SFML/Audio/OutputSoundFile.hpp \
    External/SFML/include/SFML/Audio/Sound.hpp \
    External/SFML/include/SFML/Audio/SoundBuffer.hpp \
    External/SFML/include/SFML/Audio/SoundBufferRecorder.hpp \
    External/SFML/include/SFML/Audio/SoundFileFactory.hpp \
    External/SFML/include/SFML/Audio/SoundFileFactory.inl \
    External/SFML/include/SFML/Audio/SoundFileReader.hpp \
    External/SFML/include/SFML/Audio/SoundFileWriter.hpp \
    External/SFML/include/SFML/Audio/SoundRecorder.hpp \
    External/SFML/include/SFML/Audio/SoundSource.hpp \
    External/SFML/include/SFML/Audio/SoundStream.hpp \
    External/SFML/include/SFML/Config.hpp \
    External/SFML/include/SFML/GpuPreference.hpp \
    External/SFML/include/SFML/Graphics.hpp \
    External/SFML/include/SFML/Graphics/BlendMode.hpp \
    External/SFML/include/SFML/Graphics/CircleShape.hpp \
    External/SFML/include/SFML/Graphics/Color.hpp \
    External/SFML/include/SFML/Graphics/ConvexShape.hpp \
    External/SFML/include/SFML/Graphics/Drawable.hpp \
    External/SFML/include/SFML/Graphics/Export.hpp \
    External/SFML/include/SFML/Graphics/Font.hpp \
    External/SFML/include/SFML/Graphics/Glsl.hpp \
    External/SFML/include/SFML/Graphics/Glsl.inl \
    External/SFML/include/SFML/Graphics/Glyph.hpp \
    External/SFML/include/SFML/Graphics/Image.hpp \
    External/SFML/include/SFML/Graphics/PrimitiveType.hpp \
    External/SFML/include/SFML/Graphics/Rect.hpp \
    External/SFML/include/SFML/Graphics/Rect.inl \
    External/SFML/include/SFML/Graphics/RectangleShape.hpp \
    External/SFML/include/SFML/Graphics/RenderStates.hpp \
    External/SFML/include/SFML/Graphics/RenderTarget.hpp \
    External/SFML/include/SFML/Graphics/RenderTexture.hpp \
    External/SFML/include/SFML/Graphics/RenderWindow.hpp \
    External/SFML/include/SFML/Graphics/Shader.hpp \
    External/SFML/include/SFML/Graphics/Shape.hpp \
    External/SFML/include/SFML/Graphics/Sprite.hpp \
    External/SFML/include/SFML/Graphics/Text.hpp \
    External/SFML/include/SFML/Graphics/Texture.hpp \
    External/SFML/include/SFML/Graphics/Transform.hpp \
    External/SFML/include/SFML/Graphics/Transformable.hpp \
    External/SFML/include/SFML/Graphics/Vertex.hpp \
    External/SFML/include/SFML/Graphics/VertexArray.hpp \
    External/SFML/include/SFML/Graphics/VertexBuffer.hpp \
    External/SFML/include/SFML/Graphics/View.hpp \
    External/SFML/include/SFML/Main.hpp \
    External/SFML/include/SFML/Network.hpp \
    External/SFML/include/SFML/Network/Export.hpp \
    External/SFML/include/SFML/Network/Ftp.hpp \
    External/SFML/include/SFML/Network/Http.hpp \
    External/SFML/include/SFML/Network/IpAddress.hpp \
    External/SFML/include/SFML/Network/Packet.hpp \
    External/SFML/include/SFML/Network/Socket.hpp \
    External/SFML/include/SFML/Network/SocketHandle.hpp \
    External/SFML/include/SFML/Network/SocketSelector.hpp \
    External/SFML/include/SFML/Network/TcpListener.hpp \
    External/SFML/include/SFML/Network/TcpSocket.hpp \
    External/SFML/include/SFML/Network/UdpSocket.hpp \
    External/SFML/include/SFML/OpenGL.hpp \
    External/SFML/include/SFML/System.hpp \
    External/SFML/include/SFML/System/Clock.hpp \
    External/SFML/include/SFML/System/Err.hpp \
    External/SFML/include/SFML/System/Export.hpp \
    External/SFML/include/SFML/System/FileInputStream.hpp \
    External/SFML/include/SFML/System/InputStream.hpp \
    External/SFML/include/SFML/System/Lock.hpp \
    External/SFML/include/SFML/System/MemoryInputStream.hpp \
    External/SFML/include/SFML/System/Mutex.hpp \
    External/SFML/include/SFML/System/NativeActivity.hpp \
    External/SFML/include/SFML/System/NonCopyable.hpp \
    External/SFML/include/SFML/System/Sleep.hpp \
    External/SFML/include/SFML/System/String.hpp \
    External/SFML/include/SFML/System/String.inl \
    External/SFML/include/SFML/System/Thread.hpp \
    External/SFML/include/SFML/System/Thread.inl \
    External/SFML/include/SFML/System/ThreadLocal.hpp \
    External/SFML/include/SFML/System/ThreadLocalPtr.hpp \
    External/SFML/include/SFML/System/ThreadLocalPtr.inl \
    External/SFML/include/SFML/System/Time.hpp \
    External/SFML/include/SFML/System/Utf.hpp \
    External/SFML/include/SFML/System/Utf.inl \
    External/SFML/include/SFML/System/Vector2.hpp \
    External/SFML/include/SFML/System/Vector2.inl \
    External/SFML/include/SFML/System/Vector3.hpp \
    External/SFML/include/SFML/System/Vector3.inl \
    External/SFML/include/SFML/Window.hpp \
    External/SFML/include/SFML/Window/Clipboard.hpp \
    External/SFML/include/SFML/Window/Context.hpp \
    External/SFML/include/SFML/Window/ContextSettings.hpp \
    External/SFML/include/SFML/Window/Cursor.hpp \
    External/SFML/include/SFML/Window/Event.hpp \
    External/SFML/include/SFML/Window/Export.hpp \
    External/SFML/include/SFML/Window/GlResource.hpp \
    External/SFML/include/SFML/Window/Joystick.hpp \
    External/SFML/include/SFML/Window/Keyboard.hpp \
    External/SFML/include/SFML/Window/Mouse.hpp \
    External/SFML/include/SFML/Window/Sensor.hpp \
    External/SFML/include/SFML/Window/Touch.hpp \
    External/SFML/include/SFML/Window/VideoMode.hpp \
    External/SFML/include/SFML/Window/Window.hpp \
    External/SFML/include/SFML/Window/WindowHandle.hpp \
    External/SFML/include/SFML/Window/WindowStyle.hpp \
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

RESOURCES += \
    images.qrc \
    vehicles.qrc

DISTFILES += \
    External/SFML/bin/openal32.dll \
    External/SFML/bin/sfml-audio-2.dll \
    External/SFML/bin/sfml-audio-d-2.dll \
    External/SFML/bin/sfml-graphics-2.dll \
    External/SFML/bin/sfml-graphics-d-2.dll \
    External/SFML/bin/sfml-network-2.dll \
    External/SFML/bin/sfml-network-d-2.dll \
    External/SFML/bin/sfml-system-2.dll \
    External/SFML/bin/sfml-system-d-2.dll \
    External/SFML/bin/sfml-window-2.dll \
    External/SFML/bin/sfml-window-d-2.dll \
    External/SFML/lib/cmake/SFML/SFMLConfig.cmake \
    External/SFML/lib/cmake/SFML/SFMLConfigDependencies.cmake \
    External/SFML/lib/cmake/SFML/SFMLConfigVersion.cmake \
    External/SFML/lib/cmake/SFML/SFMLSharedTargets-debug.cmake \
    External/SFML/lib/cmake/SFML/SFMLSharedTargets-release.cmake \
    External/SFML/lib/cmake/SFML/SFMLSharedTargets.cmake \
    External/SFML/lib/cmake/SFML/SFMLStaticTargets-debug.cmake \
    External/SFML/lib/cmake/SFML/SFMLStaticTargets-release.cmake \
    External/SFML/lib/cmake/SFML/SFMLStaticTargets.cmake \
    External/SFML/lib/libFLAC.a \
    External/SFML/lib/libfreetype.a \
    External/SFML/lib/libogg.a \
    External/SFML/lib/libopenal32.a \
    External/SFML/lib/libsfml-audio-d.a \
    External/SFML/lib/libsfml-audio-s-d.a \
    External/SFML/lib/libsfml-audio-s.a \
    External/SFML/lib/libsfml-audio.a \
    External/SFML/lib/libsfml-graphics-d.a \
    External/SFML/lib/libsfml-graphics-s-d.a \
    External/SFML/lib/libsfml-graphics-s.a \
    External/SFML/lib/libsfml-graphics.a \
    External/SFML/lib/libsfml-main-d.a \
    External/SFML/lib/libsfml-main.a \
    External/SFML/lib/libsfml-network-d.a \
    External/SFML/lib/libsfml-network-s-d.a \
    External/SFML/lib/libsfml-network-s.a \
    External/SFML/lib/libsfml-network.a \
    External/SFML/lib/libsfml-system-d.a \
    External/SFML/lib/libsfml-system-s-d.a \
    External/SFML/lib/libsfml-system-s.a \
    External/SFML/lib/libsfml-system.a \
    External/SFML/lib/libsfml-window-d.a \
    External/SFML/lib/libsfml-window-s-d.a \
    External/SFML/lib/libsfml-window-s.a \
    External/SFML/lib/libsfml-window.a \
    External/SFML/lib/libvorbis.a \
    External/SFML/lib/libvorbisenc.a \
    External/SFML/lib/libvorbisfile.a \
    KX_Pult/protocols.conf
