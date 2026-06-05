cmake_minimum_required(VERSION 3.14)
project(link_shortener)

find_package(
    userver
    COMPONENTS postgresql
    REQUIRED
)

add_executable(${PROJECT_NAME} "main.cpp")

add_library(${PROJECT_NAME}_objs OBJECT
    src/index.hpp
    src/index.cpp
    src/links_cache.hpp
    src/links_cache.cpp
    src/link_maker_handler.hpp
    src/link_maker_handler.cpp
    src/redirect_handler.hpp
    src/redirect_handler.cpp
)
target_link_libraries(${PROJECT_NAME}_objs userver::postgresql)
target_include_directories(${PROJECT_NAME}_objs PUBLIC src)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_objs)


 
userver_testsuite_add_simple()
 