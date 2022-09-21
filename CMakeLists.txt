#
# Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
#
cmake_minimum_required(VERSION 3.1)
project(STDIX C)

set(CMAKE_C_STANDARD 11)

add_library(STDIX src/stdix.c src/stdix.h)
add_test(STDIX test/stdix_test.c test/stdix_test.h)
target_link_libraries(STDIX PRIVATE m)

add_executable(STDIX_test test/stdix_test.c test/stdix_test.h src/stdix.c src/stdix.h)
target_link_libraries(STDIX_test PRIVATE m)