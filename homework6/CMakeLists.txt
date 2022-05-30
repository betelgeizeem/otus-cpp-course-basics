cmake_minimum_required(VERSION 3.5)

project(homework6)

add_executable(containers containers.cpp)
set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

