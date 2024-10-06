cmake_minimum_required(VERSION 3.5)
project(Emulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/out)

add_subdirectory(Sender)
add_subdirectory(Receiver)

