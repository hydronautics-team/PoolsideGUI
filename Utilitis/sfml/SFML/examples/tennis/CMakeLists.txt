
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/tennis)

# all source files
set(SRC ${SRCROOT}/Tennis.cpp)
if (SFML_OS_IOS)
    set(RESOURCES
            resources/ball.wav
            resources/tuffy.ttf)
    set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()

# define the pong target
sfml_add_example(tennis GUI_APP
                 SOURCES ${SRC}
                 BUNDLE_RESOURCES ${RESOURCES}
                 DEPENDS sfml-audio sfml-graphics
                 RESOURCES_DIR resources)
