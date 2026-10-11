cmake_minimum_required(VERSION 3.16)
project(qcustomplot-test-app LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Select the Qt version with -DCMAKE_PREFIX_PATH=/opt/qt/<version>/gcc_64
find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)

if(NOT TARGET qcustomplot)
    add_subdirectory(../qcustomplot qcustomplot-build)
endif()

add_executable(test_app main.cpp)
target_include_directories(test_app PRIVATE ../qcustomplot)
target_link_libraries(test_app PRIVATE qcustomplot Qt6::Widgets Qt6::PrintSupport)
