# SPDX-FileCopyrightText: 2026 Igor Mironchik <igor.mironchik@gmail.com>
# SPDX-License-Identifier: MIT

project(github-release-test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(SRC main.cpp)

add_executable(github-release-test WIN32 ${SRC})

target_link_libraries(github-release-test github-release Qt6::Core)
