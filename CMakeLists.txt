cmake_minimum_required(VERSION 3.16)

project(lmap VERSION 0.1 LANGUAGES CXX)
option(BUILD_WITH_QT "require Qt to build" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Проверка поддержки SSE4.2 
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-msse4.2" COMPILER_SUPPORTS_SSE42)
set(PROJECT_SOURCES
    main.cpp
    i_model.h
    modelimpl.h modelimpl.cpp
    socket.h
    cli_presenter.cpp cli_presenter.h
        portscanner.cpp       
        portscanner.h         
    outputformatter.h outputformatter.cpp)

set(Import )
if(BUILD_WITH_QT)
    set (Import ${Import} Qt${QT_VERSION_MAJOR}::Widgets)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qt_presenter.h qt_presenter.cpp
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
    # list(APPEND CMAKE_PREFIX_PATH "/usr/lib")
    find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets Core)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(lmap
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES})
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
    if(${QT_VERSION} VERSION_LESS 6.1.0)
        set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lmap)
    endif()   
else()
    add_executable(lmap ${PROJECT_SOURCES})
endif()
# ТЕПЕРЬ, применяем оптимизации SSE
if(COMPILER_SUPPORTS_SSE42)
    message(STATUS "SSE4.2 supported, enabling optimizations")
    target_compile_options(lmap PRIVATE "-msse4.2")
    target_compile_definitions(lmap PRIVATE "__SSE4_2__")
else()
    message(STATUS "SSE4.2 not supported, using standard code path")
endif()
if(WIN32)
    set (Import ${Import} wsock32 ws2_32)
endif()
target_link_libraries(lmap PUBLIC ${Import})

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

if(BUILD_WITH_QT)
    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(lmap)
    endif()
endif()
