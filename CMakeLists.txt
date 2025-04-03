cmake_minimum_required(VERSION 3.16)

project(lmap VERSION 0.1 LANGUAGES CXX)
option(BUILD_WITH_QT "require Qt to build" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Проверка поддержки SSE4.2 
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-msse4.2" COMPILER_SUPPORTS_SSE42)
set(PROJECT_SOURCES
    i_model.h
    modelimpl.h modelimpl.cpp
    socket.h
    cli_presenter.cpp cli_presenter.h
    portscanner.cpp portscanner.h         
    outputformatter.h outputformatter.cpp)

set(Import )
if(BUILD_WITH_QT)
    set (Import ${Import} Qt${QT_VERSION_MAJOR}::Widgets)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        gui_main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qt_presenter.h qt_presenter.cpp
    )
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core)
    qt_add_executable(lmap
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    set(PROJECT_SOURCES ${PROJECT_SOURCES} cli_main.cpp)
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
