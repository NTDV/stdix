//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#include "stdix_test.h" //todo Add test

int main() {
    init_console();
    long a, b, c;

    read_longs(3, &a, &b, &c);
    printf("%lld %lld %lld", a, b, c);
}