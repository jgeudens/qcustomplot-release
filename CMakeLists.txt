cmake_minimum_required(VERSION 3.16)
project(qcustomplot-release LANGUAGES CXX)

option(QCP_BUILD_TEST_APP "Build the test application" ON)

add_subdirectory(qcustomplot)

if(QCP_BUILD_TEST_APP)
    add_subdirectory(test-app)
endif()
