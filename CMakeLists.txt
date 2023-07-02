cmake_minimum_required(VERSION 3.16)

project(HueController VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(HueController
    main.cpp hueapi.h hueapi.cpp
)

qt_add_qml_module(HueController
	URI HueController 
    VERSION 1.0
    QML_FILES Main.qml
)

qt_add_resources(HueController ssl_cert
    PREFIX "/certificates"
    FILES ${CMAKE_SOURCE_DIR}/Certificate/ssl.pem
)

set_target_properties(HueController PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

find_package(OpenSSL REQUIRED)
target_link_libraries(HueController
    PRIVATE Qt6::Quick
)

install(TARGETS HueController
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
