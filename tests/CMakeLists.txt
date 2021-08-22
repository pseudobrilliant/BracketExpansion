
project(${CMAKE_PROJECT_NAME}_tests)

# Clone Google Test
set(GOOGLETEST_DIR ${CMAKE_SOURCE_DIR}/tests/lib/googletest)
if(NOT EXISTS ${GOOGLETEST_DIR})
    find_package(Git REQUIRED)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest ${GOOGLETEST_DIR}
    )
endif()

add_subdirectory(lib/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${CMAKE_PROJECT_NAME}_tests BracketExpansionTest.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_tests gtest gtest_main)
target_link_libraries(${CMAKE_PROJECT_NAME}_tests ${CMAKE_PROJECT_NAME}_lib)