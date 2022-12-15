//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//

#ifndef STDIX_STRING_H
#define STDIX_STRING_H

#define __PRIVATE_STR_VALUE(x) __PRIVATE_STR(x)
#define __PRIVATE_STR(x) #x

#define READLINE_BUFFER 80


#include <stdint.h>
#include "stdix.h"

typedef char* string;

typedef struct {
    string chars;
    size_t length;
} ix_string;

ix_string* ix_string_readline();
ix_string* ix_string_readline_stream(FILE* stream);
void ix_reverse(ix_string* string);
void ix_string_spliterator(ix_string* string, bool (*delimiter)(char), void (*fun)(char*,char*));
void ix_string_free(ix_string* string);

#endif //STDIX_STRING_H
