//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#include "stdix_test.h"

int main() {
    init_console();
    ulong a;

    read_ulong(&a);
    printf("%llu", a);
}