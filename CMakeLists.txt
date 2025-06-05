cmake_minimum_required(VERSION 3.19)
project(Cmon LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)  # for Qt + MSVC
endif()

#TODO this is tmp solution for msys2 system
if(WIN32)
  set(Qt6_DIR "C:/msys64/mingw64/lib/cmake/Qt6")
endif()
find_package(QT NAMES Qt6 REQUIRED COMPONENTS LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets LinguistTools Charts PrintSupport)


file(GLOB SOURCES "src/*.cpp" "src/*.ui")
file(GLOB HEADERS "include/*.h")
if(WIN32)
  file(GLOB OS_SOURCES "src/windows/*.cpp")
  file(GLOB OS_HEADERS "include/windows/*.h")
elseif(UNIX)
  file(GLOB OS_SOURCES "src/linux/*.cpp")
  file(GLOB OS_HEADERS "include/linux/*.h")
endif()

FetchContent_Declare(qcustomplot
  URL https://www.qcustomplot.com/release/2.1.1/QCustomPlot-source.tar.gz
)
FetchContent_MakeAvailable(qcustomplot)
add_library(qcustomplot
  "${qcustomplot_SOURCE_DIR}/qcustomplot.h"
  "${qcustomplot_SOURCE_DIR}/qcustomplot.cpp"
)

qt_standard_project_setup()

#TRANSLATIONS
file(GLOB TS_FILES "translations/*.ts")

qt_add_executable(Cmon
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${OS_SOURCES}
    ${OS_HEADERS}
)
qt_add_translations(
    TARGETS Cmon
    TS_FILES ${TS_FILES}
    QM_FILES_OUTPUT_VARIABLE QM_FILES
)
target_include_directories(qcustomplot PUBLIC
  "${qcustomplot_SOURCE_DIR}"
  "include"
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

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Charts
        qcustomplot
)

include(GNUInstallDirs)


install(TARGETS Cmon
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES ${QM_FILES} DESTINATION "translations")
qt_generate_deploy_app_script(
    TARGET Cmon
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
