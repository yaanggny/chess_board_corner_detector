cmake_minimum_required(VERSION 2.8)

project(test_MultichessboardExtraction)

find_package(OpenCV REQUIRED)

aux_source_directory(. SRCS)

add_executable(${PROJECT_NAME} ${SRCS}
    )
    
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
