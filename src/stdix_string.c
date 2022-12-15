//
// Created by Danila Valkovets (dahnh33@gmail.com) on 27.11.2022.
//
#include "stdix_string.h"

ix_string* ix_string_init_manual(size_t length) {
    if (length == 0) return NULL;

    ix_string* string = malloc(sizeof *string);
    string->length = length;
    string->chars = malloc(string->length * sizeof *(string->chars));

    if (string->chars == NULL) return NULL;
    return string;
}

ix_string* ix_string_init() {
    return ix_string_init_manual(0);
}

ix_string* ix_string_init_from(const char* chars, size_t length) {
    ix_string* string = ix_string_init_manual(length);
    for (size_t i = 0; i < length; ++i) string->chars[i] = chars[i];
    string->length = length;
    return string;
}

STATUS ix_string_ensure_capacity(ix_string* array, size_t new_size) {
    if (new_size < array->length) return OK;
    array->chars = realloc(array->chars, new_size * sizeof *(array->chars));
    if(array->chars == NULL) return ALLOCATION_ERROR;
    return OK;
}

STATUS ix_string_shift(char* chars, const size_t offset, const size_t length) {
    memmove(chars + offset, chars, length * sizeof *chars);
    if (chars != NULL) return OK;
    else return MEMORY_MOVE_ERROR;
}


STATUS ix_string_insert_at(ix_string* array, size_t index, char value) {
    if (array->length == SIZE_MAX) return VARIABLE_OVERFLOW;
    STATUS state;
    if (index >= array->length) {
        if ((state = ix_string_ensure_capacity(array, array->length + 1)) != OK) return state;
        array->chars[array->length] = value;
        ++(array->length);
    } else {
        if ((state = ix_string_ensure_capacity(array, array->length + 1)) != OK) return state;
        ix_string_shift(array->chars + index, 1, array->length - index);
        array->chars[index] = value;
        ++(array->length);
    }
    state = OK;
    return state;
}

STATUS ix_string_remove_at(ix_string* string, size_t index) {
    if (string->length == 0) return OPERATION_NOT_ALLOWED;
    if (index >= string->length) return INVALID_ARGUMENT;
    STATUS state;
    if ((state = ix_string_shift(string->chars + index + 1, -1, string->length - index - 1)) != OK) return state;
    --(string->length);
    return OK;
}

char* ix_string_get(ix_string* string) {
    return string->chars;
}

STATUS ix_string_get_char(ix_string* string, size_t index, char* result) {
    if (index >= string->length) return INDEX_OUT_OF_ARRAY;
    *result = string->chars[index];
    return OK;
}

ix_string* ix_string_readline() {
    char* buffer = malloc((READLINE_BUFFER + 1) * sizeof *buffer);
    char* chars = NULL;
    size_t length = 0;
    int scanned;

    do {
        scanned = scanf("%" __PRIVATE_STR_VALUE(READLINE_BUFFER) "[^\n]", buffer);
        if (scanned > 0) {
            length += ix_strlen(buffer);
            if (chars == NULL) {
                chars = realloc(chars, length + 1);
                memcpy(chars, buffer, (length + 1) * sizeof *buffer);
            } else {
                chars = realloc(chars, length + 1);
                ix_strcat(chars, buffer);
            }
        } else if (scanned < 0) {
            free(chars);
            chars = NULL;
            continue;
        } else scanf("%*c");
    } while(scanned > 0);

    ix_string* string;
    if (length > 0 || (length == 0 && scanned != -1)) {
        string = malloc(sizeof *string);
        string->length = length;
        if(chars == NULL) chars = malloc(sizeof *chars);
        string->chars = chars;
        string->chars[length] = '\0';
    } else string = NULL;

    free(buffer);
    return string;
}

ix_string* ix_string_readline_stream(FILE* stream) {
    char* buffer = malloc((READLINE_BUFFER + 1) * sizeof *buffer);
    char* chars = NULL;
    size_t length = 0;
    int scanned;

    do {
        scanned = fscanf(stream, "%" __PRIVATE_STR_VALUE(READLINE_BUFFER) "[^\n]", buffer);
        if (scanned > 0) {
            length += ix_strlen(buffer);
            if (chars == NULL) {
                chars = realloc(chars, length + 1);
                memcpy(chars, buffer, (length + 1) * sizeof *buffer);
            } else {
                chars = realloc(chars, length + 1);
                ix_strcat(chars, buffer);
            }
        } else if (scanned < 0) {
            free(chars);
            chars = NULL;
            continue;
        } else fscanf(stream, "%*c");
    } while(scanned > 0);

    ix_string* string;
    if (length > 0 || (length == 0 && scanned != -1)) {
        string = malloc(sizeof *string);
        string->length = length;
        if(chars == NULL) chars = malloc(sizeof *chars);
        string->chars = chars;
        string->chars[length] = '\0';
    } else string = NULL;

    free(buffer);
    return string;
}

void ix_reverse(ix_string* string) {
    for (size_t i = 0; i < string->length / 2; ++i) {
        char temp = string->chars[i];
        string->chars[i] = string->chars[string->length - i - 1];
        string->chars[string->length - i - 1] = temp;
    }
}

void ix_string_spliterator(ix_string* string, bool (*delimiter)(char), void (*fun)(char*,char*)) {
    string_spliterator(string->chars, string->length, delimiter, fun);
}

void ix_string_free(ix_string* string) {
    if (string != NULL) {
        free(string->chars);
        free(string);
    }
}