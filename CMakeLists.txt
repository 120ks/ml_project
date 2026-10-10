cmake_minimum_required (VERSION 3.10 )

project(ml_project)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

add_executable(${PROJECT_NAME}
    main.cpp

    src/matrix/matrix.cpp
    src/matrix/matrix_operations.cpp 
    src/feed_forward.cpp
    src/matrix/matrix_functions.cpp
    src/matrix/matrix_iterator.h
    src/matrix/matrix_container.cpp
    src/matrix/matrix_view.h
    src/matrix/matrix_view.cpp
    )

target_include_directories(ml_project  PRIVATE
    src
    src/matrix
    )
