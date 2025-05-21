cmake_minimum_required(VERSION 3.19)
project(Cmon LANGUAGES CXX)
include(FetchContent)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Charts PrintSupport)
FetchContent_Declare(qcustomplot
  URL https://www.qcustomplot.com/release/2.1.1/QCustomPlot-source.tar.gz
)
FetchContent_MakeAvailable(qcustomplot)
add_library(qcustomplot
  "${qcustomplot_SOURCE_DIR}/qcustomplot.h"
  "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp"
)

qt_standard_project_setup()

qt_add_executable(Cmon
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    systemmonitor.h systemmonitor.cpp
    linuxsystemmonitor.h linuxsystemmonitor.cpp

    monitorplot.h monitorplot.cpp
)
qt_add_translations(
    TARGETS Cmon
    TS_FILES Cmon_ru_RU.ts
)
target_include_directories(qcustomplot PUBLIC
  "${qcustomplot_SOURCE_DIR}"
  )

set(Qt6Libs Core Widgets PrintSupport)
foreach(i IN LISTS Qt6Libs)
  target_link_libraries(qcustomplot PRIVATE
    Qt6::${i}
    )
endforeach()
set_target_properties(qcustomplot PROPERTIES
  AUTOMOC ON
  )

target_link_libraries(Cmon
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Charts
        qcustomplot
)


include(GNUInstallDirs)

install(TARGETS Cmon
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Cmon
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
