# SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
# SPDX-License-Identifier: MIT

project(github-release-test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test)

add_executable(github-release-tool main_tool.cpp)

target_link_libraries(github-release-tool github-release Qt6::Core)

add_executable(github-release-button WIN32 main_button.cpp)

target_link_libraries(github-release-button github-release Qt6::Widgets Qt6::Core)

add_executable(github-release-autotest main_autotest.cpp)

target_link_libraries(github-release-autotest github-release Qt6::Test Qt6::Core)

add_test(NAME github-release-autotest
    COMMAND github-release-autotest${CMAKE_EXECUTABLE_SUFFIX}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../bin)
