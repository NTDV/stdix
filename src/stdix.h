//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#ifndef STDIX_H
#define STDIX_H

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#define uint unsigned int
#define long long long
#define ulong unsigned long

#define STRSTR_ALL_MODE_DISTINCT    1
#define STRSTR_ALL_MODE_EACH        0

unsigned long strstr_all_mode(const char *string, const char *find, int mode);
unsigned long strstr_all_(const char *string, const char *find);

void vsscanf_safe_nargs(int n, const char* format, va_list args);
void vsscanf_safe_n(int n, const char* format, ...);
void vsscanf_safe_(const char* format, ...);

int num_length_u(unsigned long n);
int num_length_(long n);

int numtype_maxlength_s(int size, int hasSign);
int numtype_maxlength_(int size);

//todo Encapsulate these to int read_{type}_b({type}* n, char* buffer, size_t size)
void read_double(double* n);
void read_float(float* n);
void read_int(int* n);
void read_uint(uint* n);
void read_long(long *n);
void read_ulong(ulong* n);

void read_doubles(int count, ...);
void read_floats(int count, ...);
void read_ints(int count, ...);
void read_uints(int count, ...);
void read_longs(int count, ...);
void read_ulongs(int count, ...);

void print_ii();

void init_console();

//todo Implement 'generics' aka polymorphism\overloading

#endif //STDIX_H
