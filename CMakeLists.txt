cmake_minimum_required(VERSION 3.0.2)
project(px4_quad_slam_simulation)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS roscpp nav_msgs tf)
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(map_baselink_broadcaster src/map_baselink_broadcaster.cpp)
target_link_libraries(map_baselink_broadcaster ${catkin_LIBRARIES})