cmake_minimum_required(VERSION 3.10)
project(usb)

add_executable(usb main.cpp)
target_link_libraries(usb PRIVATE usb-1.0)
