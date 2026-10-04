cmake_minimum_required (VERSION 3.10 )

project(ml_project)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    src/matrix.cpp
    src/self_attention_layer.cpp 
    src/feed_forward.cpp
    )

target_include_directories(ml_project  PRIVATE
    src
    )
