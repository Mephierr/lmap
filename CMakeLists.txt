cmake_minimum_required(VERSION 3.16)

project(lmap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(BUILD_WITH_QT "require Qt to build" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    main.cpp
    IModel.h
    modelimpl.h modelimpl.cpp
    socket.h
    outputformatter.h outputformatter.cpp)
if(BUILD_WITH_QT)
    message("building with qt")
    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qt_presenter.h qt_presenter.cpp
        )
endif()

if(BUILD_WITH_QT) 
    message("AFEOGJOOIJ$JIOGOAG(%U)(Q@$%U)@*U$)%@*J$TJIHO$WJIO")
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

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
else()
    add_executable(lmap ${PROJECT_SOURCES})
endif()
set(Import )
if(WIN32)
    set (Import ${Import} wsock32 ws2_32)
endif()
if(BUILD_WITH_QT) 
    set (Import ${Import} Qt${QT_VERSION_MAJOR}::Widgets)
endif()
target_link_libraries(lmap PRIVATE ${Import})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(BUILD_WITH_QT)
    if(AND ${QT_VERSION} VERSION_LESS 6.1.0)
        set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lmap)
    endif()
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
