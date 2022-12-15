#
# Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
#
cmake_minimum_required(VERSION 3.1)
project(STDIX C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/include/readline)

add_library(STDIX
        src/stdix.h src/stdix.c
        src/stdix_dynamicarray.h src/stdix_dynamicarray.c
        src/stdix_linkedtree.h src/stdix_linkedtree.c
        src/stdix_linkedtreeset.h src/stdix_linkedtreeset.c
        src/stdix_dynamicarray.h src/stdix_dynamicarray.c
        src/stdix_string.h src/stdix_string.c
        src/stdix_sorting.h src/stdix_sorting.c)
add_test(STDIX
        test/stdix_test.h test/stdix_test.c)
target_link_libraries(STDIX PRIVATE m)

add_executable(STDIX_test
        test/stdix_test.h test/stdix_test.c
        src/stdix.h src/stdix.c
        src/stdix_dynamicarray.h src/stdix_dynamicarray.c
        src/stdix_linkedtree.h src/stdix_linkedtree.c
        src/stdix_linkedtreeset.h src/stdix_linkedtreeset.c
        src/stdix_dynamicarray.h src/stdix_dynamicarray.c
        src/stdix_string.h src/stdix_string.c
        src/stdix_sorting.h src/stdix_sorting.c)
target_link_libraries(STDIX_test PRIVATE m readline)