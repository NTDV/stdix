//
// Created by Danila Valkovets (dahnh33@gmail.com) on 27.11.2022.
//
#include "stdix_test.h" //todo Add test

bool delimiter(const char symbol) {
    return symbol == ' ' || symbol == '\t' || symbol == '\0';
}

int main() {
    init_console();

#ifdef OWN
    dynamicarray* array = dynamicarray_init();
    ix_string* string;
    while ((string = ix_string_readline()) != NULL) dynamicarray_insert_at(array, array->size, string);
    printf("\n");
    for (int i = 0; i < array->size; ++i) {
        ix_string_spliterator(array->array[i], delimiter, reverse_char_sequence);
        printf("%s\n", ((ix_string*)(array->array[i]))->chars);
    }
    for (size_t i = 0; i < array->size; ++i) ix_string_free(array->array[i]);
    dynamicarray_free(array);
#endif

#ifdef LIB
    dynamicarray* array = dynamicarray_init();
    char* string;
    while ((string = readline(NULL)) != NULL) dynamicarray_insert_at(array, array->size, string);
    for (int i = 0; i < array->size; ++i) {
        string_spliterator(array->array[i], strlen(array->array[i]), delimiter, reverse_char_sequence);
        printf("%s\n", (char*) array->array[i]);
    }
    for (size_t i = 0; i < array->size; ++i) free(array->array[i]);
    dynamicarray_free(array);
    rl_clear_history();
#endif

    return 0;
}