//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#include "stdix_test.h" //todo Add test

int main() {
    double x, e;
    ulong n;
    read_doubles(2, &x, &e);
    while (e < 0) {
        print_ii();
        read_double(&e);
    }
    read_ulong(&n);

    printf("SIN\n(std) %.*f\n(own) %.*f\n", DECIMAL_DIG, sin(deg_to_rad(x)), DECIMAL_DIG, taylor_sin_deg(x, e, n));
    printf("EXP\n(std) %.*f\n(own) %.*f\n", DECIMAL_DIG, exp(-x*x), DECIMAL_DIG, taylor_exp_notxx(x, e, n));
}