cmake_minimum_required(VERSION 3.16)

project(lmap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка поддержки SSE4.2 
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-msse4.2" COMPILER_SUPPORTS_SSE42)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        portscanner.cpp       
        portscanner.h          
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lmap
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        socket.h
        presenter.h presenter.cpp
        IModel.h
        modelimpl.h modelimpl.cpp
        outputformatter.h outputformatter.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lmap APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(lmap SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(lmap
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ТЕПЕРЬ, применяем оптимизации SSE
if(COMPILER_SUPPORTS_SSE42)
    message(STATUS "SSE4.2 supported, enabling optimizations")
    target_compile_options(lmap PRIVATE "-msse4.2")
    target_compile_definitions(lmap PRIVATE "__SSE4_2__")
else()
    message(STATUS "SSE4.2 not supported, using standard code path")
endif()

set(Import )
if(WIN32)
  set (Import ${Import} wsock32 ws2_32)
endif()
target_link_libraries(lmap PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Import})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lmap)
endif()
set_target_properties(lmap PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lmap
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lmap)
endif()
