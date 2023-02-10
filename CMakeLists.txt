cmake_minimum_required(VERSION 3.18)

project(video_devices)

find_package(OpenCV REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Set files to be compiled
file(GLOB HEADER_FILES 
    ${PROJECT_SOURCE_DIR}/include/*.h
)
file(GLOB SRC_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OpenCV_LIBS}
    mfplat
    mf
)
