cmake_minimum_required(VERSION 3.10)

project(Get_Pos)




add_executable(Get_Pos get_pos.cpp)

target_link_libraries(Get_Pos PRIVATE realsense2)
