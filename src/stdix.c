//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#include <stdlib.h>
#include <errno.h>
#include "stdix.h" //todo Add documentation

void init_console() {
    setlocale(LC_ALL, "");
}

void print_ii() {
    printf("Invalid input!\r\n");
}

void print_wi() {
    printf(">");
    //todo Implement detecting strange terminal behaviour, such as run.processes.with.pty (see https://youtrack.jetbrains.com/issue/CPP-2580)
    //fflush(stdout);
}

ulong strstr_all_mode(const char *string, const char *find, const int mode){
    unsigned long count = 0;
    const char *tmp = string;
    unsigned long inc = mode ? strlen(find) : 1;
    while((tmp = strstr(tmp, find)))
    {
        count += inc;
        ++tmp;
    }
    return count;
}

ulong strstr_all_(const char *string, const char *find) {
    return strstr_all_mode(string, find, STRSTR_ALL_MODE_DISTINCT);
}

void vsscanf_safe_nargs(const int n, const char* format, va_list args) {
    char *buffer = NULL;
    size_t size = 0;
    print_wi();
    while ((getline(&buffer, &size, stdin) <= 0 || vsscanf(buffer, format, args) != n)) {
        print_ii();
        print_wi();
    }
}

void vsscanf_safe_n(const int n, const char* format, ...) {
    va_list args;
    va_start(args, format);
    vsscanf_safe_nargs(n, format, args);
}

void vsscanf_safe_(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vsscanf_safe_nargs((int)(strstr_all_(format, "%") - strstr_all_(format, "%%")), format, args);
}

int num_length_u(unsigned long n) {
    int count = 1;
    while ((n /= 10)) { ++count; }
    return count;
}

int num_length_(long n) {
    int count = 1;
    while ((n /= 10)) { ++count; }
    return count;
}

int numtype_maxlength_s(const int size, const int hasSign) {
    return num_length_u((unsigned long) pow(2, 8 * (size - hasSign)));
}

int numtype_maxlength_(const int size) {
    return numtype_maxlength_s(size, 1);
}

//todo Encapsulate read_* family to one func
void read_double(double* n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_DOUBLE_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        double sign = 1;
        double order = 1.0;
        int point = 0;
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '-':
                        sign = -1;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = (double) (buffer[i] - '0');
                        break;
                    default: goto READ_DOUBLE_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n')) {
                if (buffer[i-1] == '.') goto READ_DOUBLE_ML_START;
                *n *= sign;
                return;
            } else if (buffer[0] == '0' && buffer[1] != '.') {
                goto READ_DOUBLE_ML_START;
            } else {
                switch (buffer[i]) {
                    case '.': if (i == 1 && sign == -1 || point) goto READ_DOUBLE_ML_START;
                              else point = i;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        // Implements strtod behaviour. It has precision 16 digits in bad, in common 17, in best 18. Other digits ignored.
                        if (sign == 1.0 && !point && i < 17 ||
                        (sign == 1.0 && point || sign == -1.0 && !point) && (buffer[0] == '0' && i < 19 || buffer[0] != '0' && i < 18) ||
                        sign == -1.0 && point && (buffer[0] == '0' && i < 20 || buffer[0] != '0' && i < 19)) {
                            if (point) *n += ((double) (buffer[i] - '0')) * (order /= 10);
                            else *n = *n * 10 + (double) (buffer[i] - '0');
                        } else if (!point) *n *= 10;
                        if (*n == INFINITY || *n == NAN) goto READ_DOUBLE_ML_START;
                        break;
                    case EOF: case '\r': case '\n': if (i > 1 || (i == 1 && sign != -1)) {
                        *n *= sign;
                        return;
                    }
                    default: goto READ_DOUBLE_ML_START;
                }
            }
        }
    }
}

void read_float(float* n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_FLOAT_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        float sign = 1;
        float order = 1.0f;
        int point = 0;
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '-':
                        sign = -1;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = (float) (buffer[i] - '0');
                        break;
                    default: goto READ_FLOAT_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n')) {
                if (buffer[i-1] == '.') goto READ_FLOAT_ML_START;
                *n *= sign;
                return;
            } else if (buffer[0] == '0' && buffer[1] != '.') {
                goto READ_FLOAT_ML_START;
            } else {
                switch (buffer[i]) {
                    case '.': if (i == 1 && sign == -1 || point) goto READ_FLOAT_ML_START;
                              else point = i;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        // Implements strtof behaviour.
                        if (sign == 1.0 && !point && i < 17 ||
                            (sign == 1.0 && point || sign == -1.0 && !point) && (buffer[0] == '0' && i < 19 || buffer[0] != '0' && i < 18) ||
                            sign == -1.0 && point && (buffer[0] == '0' && i < 20 || buffer[0] != '0' && i < 19)) {
                            if (point) *n += ((float) (buffer[i] - '0')) * (order /= 10);
                            else *n = *n * 10 + (float) (buffer[i] - '0');
                        } else if (!point) *n *= 10;
                        if (*n == INFINITY || *n == NAN) goto READ_FLOAT_ML_START;
                        break;
                    case EOF: case '\r': case '\n': if (i > 1 || (i == 1 && sign != -1)) {
                            *n *= sign;
                            return;
                        }
                    default: goto READ_FLOAT_ML_START;
                }
            }
        }
    }
}

void read_int(int* n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_INT_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '-':
                        *n = -1;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = buffer[i] - '0';
                        break;
                    default: goto READ_INT_ML_START;
                }
            } else if (*n != 0) {
                int new;
                switch (buffer[i]) {
                    case '0': if (i == 1 && *n == -1) goto READ_INT_ML_START;
                    case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        if (i == 1 && *n == -1) new = *n * (buffer[i] - '0');
                        else if (*n > 0)        new = *n * 10 + (buffer[i] - '0');
                        else                    new = *n * 10 - (buffer[i] - '0');

                        if (*n > 0 && new < 0 || *n < 0 && new > 0) goto READ_INT_ML_START;
                        else *n = new;
                        break;
                    case EOF: case '\r': case '\n': if (i > 1 || (i == 1 && *n != -1)) return;
                    default: goto READ_INT_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n') && (i > 1 || (i == 1 && *n != -1))) return;
            else goto READ_INT_ML_START;
        }
    }
}

void read_uint(uint* n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_UINT_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = buffer[i] - '0';
                        break;
                    default: goto READ_UINT_ML_START;
                }
            } else if (*n != 0) {
                uint digit;
                switch (buffer[i]) {
                    case '0': case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        digit = (buffer[i] - '0');
                        if (*n > UINT_MAX / 10 - digit) goto READ_UINT_ML_START;
                        else *n = *n * 10 + (buffer[i] - '0');
                        break;
                    case EOF: case '\r': case '\n': return;
                    default: goto READ_UINT_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n') && (i > 1 || (i == 1 && *n != -1))) return;
            else goto READ_UINT_ML_START;
        }
    }
}

void read_long(long *n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_LONG_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '-':
                        *n = -1;
                        break;
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = buffer[i] - '0';
                        break;
                    default: goto READ_LONG_ML_START;
                }
            } else if (*n != 0) {
                long new;
                switch (buffer[i]) {
                    case '0': if (i == 1 && *n == -1) goto READ_LONG_ML_START;
                    case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        if (i == 1 && *n == -1) new = *n * (buffer[i] - '0');
                        else if (*n > 0)        new = *n * 10 + (buffer[i] - '0');
                        else                    new = *n * 10 - (buffer[i] - '0');

                        if (*n > 0 && new < 0 || *n < 0 && new > 0) goto READ_LONG_ML_START;
                        else *n = new;
                        break;
                    case EOF: case '\r': case '\n': if (i > 1 || (i == 1 && *n != -1)) return;
                    default: goto READ_LONG_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n') && (i > 1 || (i == 1 && *n != -1))) return;
            else goto READ_LONG_ML_START;
        }
    }
}

void read_ulong(ulong* n) {
    char *buffer = NULL;
    size_t size = 0;
    while (1) {
        READ_ULONG_ML_START:
        if (size) print_ii();
        *n = 0;
        print_wi();
        getline(&buffer, &size, stdin);
        for (int i = 0; i < size; ++i) {
            if (!i) {
                switch (buffer[i]) {
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        *n = buffer[i] - '0';
                        break;
                    default: goto READ_ULONG_ML_START;
                }
            } else if (*n != 0) {
                ulong digit;
                switch (buffer[i]) {
                    case '0': case '1': case '2': case '3':
                    case '4': case '5': case '6':
                    case '7': case '8': case '9':
                        digit = (buffer[i] - '0');
                        if (*n > ULLONG_MAX / 10 - digit) goto READ_ULONG_ML_START;
                        else *n = *n * 10 + (buffer[i] - '0');
                        break;
                    case EOF: case '\r': case '\n': return;
                    default: goto READ_ULONG_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n') && (i > 1 || (i == 1 && *n != -1))) return;
            else goto READ_ULONG_ML_START;
        }
    }
}

void read_doubles(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_double(va_arg(args, double*));
    va_end(args);
}

void read_floats(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_float(va_arg(args, float*));
    va_end(args);
}

void read_ints(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_int(va_arg(args, int*));
    va_end(args);
}

void read_uints(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_uint(va_arg(args, uint*));
    va_end(args);
}

void read_longs(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_long(va_arg(args, long*));
    va_end(args);
}

void read_ulongs(const int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) read_ulong(va_arg(args, ulong*));
    va_end(args);
}