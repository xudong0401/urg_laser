cmake_minimum_required(VERSION 2.8.3)

project(serial_port_orocos)

find_package(catkin REQUIRED COMPONENTS rtt_ros)

include_directories(${catkin_INCLUDE_DIRS})

include_directories(${USE_OROCOS_INCLUDE_DIRS})

add_definitions(-DRTT_COMPONENT)

add_subdirectory(src)

orocos_component(${PROJECT_NAME} src/serial_port_test.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${USE_OROCOS_LIBRARIES})

orocos_generate_package(DEPENDS rtt_ros)
