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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// #define not typedef because of types.h
#define uint unsigned int
//#define long long long
#define ulong unsigned long

#define bool int
#define TRUE 1
#define FALSE 0

#define STRSTR_ALL_MODE_DISTINCT    1
#define STRSTR_ALL_MODE_EACH        0

typedef enum {
    OK = 0,
    ALLOCATION_ERROR = -1,
    INVALID_ARGUMENT = -2,
    MEMORY_MOVE_ERROR = -3,
    NOT_ENOUGH_MEMORY = -4,
    VARIABLE_OVERFLOW = -5,
    OPERATION_NOT_ALLOWED = -6,
    INDEX_OUT_OF_ARRAY = -7,
} STATUS;

ulong strstr_all_mode(const char *string, const char *find, int mode);
ulong strstr_all_(const char *string, const char *find);

void vsscanf_safe_nargs(int n, const char* format, va_list args);
void vsscanf_safe_n(int n, const char* format, ...);
void vsscanf_safe_(const char* format, ...);

int num_length_u(unsigned long n);
int num_length_(long n);

int numtype_maxlength_s(int size, int hasSign);
int numtype_maxlength_(int size);

bool is_integer(double n);
bool is_even(double n);
bool is_odd(double n);

#define TAYLOR_UNLIMITED_E 0.0
#define TAYLOR_UNLIMITED_N 0

bool greater_epsilon(double num, double e);
double deg_to_rad(double deg);
double taylor_sin_deg(double x, double e, ulong n);
double taylor_sin_rad(double x, double e, ulong n);
double taylor_exp_notxx(double x, double e, ulong n);

double iteration_nthroot(double y0, double a, uint n, double epsilon, ulong steps, ulong* N);

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

size_t ix_strlen(const char* string);
void ix_strcat(char* dest, const char* src);
void reverse_char_sequence(char* start, char* end);
void string_spliterator(char* string, size_t length, bool (*delimiter)(char), void (*fun)(char*,char*));

void print_ii();

void init_console();

#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif
void clear_console();

//todo Implement 'generics' aka polymorphism\overloading

#endif //STDIX_H
