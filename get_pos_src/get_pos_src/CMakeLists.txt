cmake_minimum_required(VERSION 3.10)

project(Get_Pos)


add_subdirectory(C:/Program Files (x86)/Intel RealSense SDK 2.0/lib/x64/realsense2.lib)

add_executable(Get_Pos get_pos.cpp)

target_link_libraries(Get_Pos PRIVATE realsense2)
