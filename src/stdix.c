//
// Created by Danila Valkovets (dahnh33@gmail.com) on 19.09.2022.
//
#include "stdix.h" //todo Add documentation

void init_console() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setlocale(LC_ALL, "");
}

void clear_console() {
    //printf ("\033[0d\033[2J");
    //system("clear");
    clrscr();
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

bool greater_epsilon(const double num, const double e) {
    return (num >= 0 && num > e) || (num < 0 && num < -e);
}

inline bool is_integer(const double n) {
    return ceil(n) == n;
}

inline bool is_even(const double n) {
    return ceil(n) == n && !((long) n % 2);
}

inline bool is_odd(const double n) {
    return ceil(n) == n && ((long) n % 2);
}

double deg_to_rad(const double deg) {
    return deg / 180 * M_PI;
}

double taylor_sin_rad(const double X, const double e, const ulong n) {
    double x = X - floor(X * M_1_PI / 2) * M_PI * 2;
    double res = 0, term = x, xx = x * x;
    for (ulong i = 1; greater_epsilon(term, e) && (!n || i <= n); ++i) {
        res += term;
        term *= (-1) * xx / ((double) ((2*i+1) * (2*i)));
    }
    return res;
}

double taylor_sin_deg(const double x, const double e, const ulong n) {
    return taylor_sin_rad(deg_to_rad(x), e, n);
}

// e^(-x*x)
double taylor_exp_notxx(const double x, const double e, const ulong n) {
    double res = 0, term = 1, xx = x * x;
    for (ulong i = 1; greater_epsilon(term, e) && (!n || i <= n); ++i) {
        res += term;
        term *= (-1) * xx / ((double) i);
        if (isinf(term) || isinf(res)) return 0;
    }
    return res;
}

// y=n√a
double iteration_nthroot(const double y0, const double a, const uint n, const double epsilon, const ulong steps, ulong* N) {
    if (y0 == 0 || a < 0 && !(n % 2) || y0 >= a) return NAN;
    if (a == 0.0 || a == 1 || a == -1 || n == 1) return a;

    double res_new,
    y = y0,
    factor = 1.0,
    $1nn = 1.0 / (n * n),
    factor1 = n + 1.0,
    factor2 = n - 1.0,
    term1 = factor1 * factor2,
    term2 = 0.5 * a * factor1,
    term3 = 0.5 / a * factor2;
    ulong i = 1;

    for (; !steps || i <= steps; ++i) {
        res_new = y * factor;
        if (epsilon != 0.0 && i>1 && !greater_epsilon(res_new - y, epsilon) || isinf(res_new) || isnan(res_new)) break;

        y = res_new;
        double factor3 = pow(y, n);
        factor = (term1 + term2 / factor3 - term3 * factor3) * $1nn;
    }

    if (N != NULL) *N = i;
    return y;
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
                free(buffer);
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
                        free(buffer);
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
                    case EOF: case '\r': case '\n':
                        free(buffer);
                        return;
                    default: goto READ_ULONG_ML_START;
                }
            } else if ((buffer[i] == EOF || buffer[i] == '\r' || buffer[i] == '\n') && (i > 1 || (i == 1 && *n != -1))) {
                free(buffer);
                return;
            } else goto READ_ULONG_ML_START;
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

size_t ix_strlen(const char* string) {
    const char *ptr;
    for (ptr = string; *ptr != '\0'; ++ptr);
    return (ptr - string);
}

void ix_strcat(char* dest, const char* src) {
    size_t destLength = ix_strlen(dest);
    dest += destLength;
    while (*src != '\0') *(dest++) = *(src++);
    *dest = '\0';
}

void reverse_char_sequence(char* start, char* end) {
    while (start < end) {
        char temp = *start;
        *(start++) = *end;
        *(end--) = temp;
    }
}

void string_spliterator(char* string, size_t length, bool (*delimiter)(char), void (*fun)(char*,char*)) {
    size_t previ = 0;
    for (size_t i = 0; i <= length; ++i) {
        if (delimiter(string[i])) {
            fun(string + previ, string + i - 1);
            previ = i + 1;
        }
    }
}