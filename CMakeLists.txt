cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(APP_BUILD_SAMPLES "build samples" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    
# app directories
set(APP_SAMPLES_DIR ./samples/)
set(APP_SOURCES_DIR ./src/)
set(APP_INCLUDE_DIR ./inc)

#project name
set(PROJECT_NAME_1 cppmsgwnd)

# project
project(${PROJECT_NAME_1} VERSION 1.0)
add_library(${PROJECT_NAME_1} SHARED ${APP_SOURCES_DIR}/CCPPMSGWND.cpp)
target_compile_definitions(${PROJECT_NAME_1} PRIVATE CPPMSGWND_EXPORTS)
target_include_directories(${PROJECT_NAME_1} PRIVATE ${APP_INCLUDE_DIR})

#project name
set(PROJECT_NAME_2 cppwndmsg)

# project
project(${PROJECT_NAME_2} VERSION 1.0)
add_library(${PROJECT_NAME_2} SHARED ${APP_SOURCES_DIR}/CCPPWNDMSG.cpp)
target_compile_definitions(${PROJECT_NAME_2} PRIVATE CPPWNDMSG_EXPORTS)
target_include_directories(${PROJECT_NAME_2} PRIVATE ${APP_INCLUDE_DIR})

# samples
if(APP_BUILD_SAMPLES)
    set(SAMPLE_PROJECTS cppmsgwnd_sample cppwndmsg_sample)
    foreach(SAMPLE_PROJECT ${SAMPLE_PROJECTS})
        project(${SAMPLE_PROJECT} VERSION 1.0)
        add_executable(${SAMPLE_PROJECT} ${APP_SAMPLES_DIR}/${SAMPLE_PROJECT}.cpp)
        target_include_directories(${SAMPLE_PROJECT} PRIVATE ${APP_INCLUDE_DIR})
        target_link_directories(${SAMPLE_PROJECT} PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    endforeach()
endif(APP_BUILD_SAMPLES)
