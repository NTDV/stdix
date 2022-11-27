//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//
#include <time.h>
#include "stdix_test.h" //todo Add test

#define MENU_STATE_LAST 5

typedef enum MENU_STATE {
    EXIT = 0,
    INITIALIZE = 1,
    INSERTION = 2,
    DELETION = 3,
    TASK = 4,
    OUTPUT = MENU_STATE_LAST
} MENU_STATE;

void print_emptyarraywarning() {
    printf("Сохраненный массив не инициализирован.\n");
}

MENU_STATE main_menu() {
    printf("0. Выход\n1. Инициализация массива\n2. Вставка нового элемента в массив по индексу\n3. Удаление элемента массива по индексу\n4. Обработка данных\n5. Вывод текущего состояния массива\n");
    MENU_STATE state;
    char *buffer = NULL;
    size_t size = 0;
    while (getline(&buffer, &size, stdin) != 2 ||
    (state = ((int) buffer[0]) - '0') < EXIT ||
    state > MENU_STATE_LAST) {
        printf("Неверный выбор меню.\n");
    }
    free(buffer);
    return state;
}

dynamicarray* initialize_array() {
    size_t size;
    printf("Инициализация массива\nВведите количество элементов:\n");
    while (TRUE) {
        read_ulong(&size);
        if (size == 0) printf("Размер должен быть положительным числом!\n");
        else break;
    }

    dynamicarray* array = dynamicarray_init_manual(size);
    for (size_t i = 0; i < size; ++i) {
        double n;
        printf("Введите элемент №%zu:\n", i+1);
        read_double(&n);
        array->array[i] = n;
    }
    return array;
}

void insertion_array(dynamicarray* array) {
    size_t index;
    printf("Вставка нового элемента в массив по индексу\nВведите номер элемента:\n");
    while (TRUE) {
        read_ulong(&index);
        if (index == 0) printf("Индекс должен быть положительным числом!\n");
        else break;
    }

    double value;
    printf("Введите значение элемента:\n");
    read_double(&value);

    dynamicarray_insert_at(array, index - 1, value);
}

void deletion_array(dynamicarray* array) {
    size_t index;
    printf("Удаление элемента массива по индексу\nВведите номер элемента:\n");
    while (TRUE) {
        read_ulong(&index);
        if (index == 0) printf("Индекс должен быть положительным числом!\n");
        else break;
    }

    dynamicarray_remove_at(array, index - 1);
}

bool task_array_check(double number) {
    uint res = 0;
    if (number < 0) number *= -1;
    if (number >= 1) {
        while (number >= 1) {
            res = ((uint) number) % 10;
            number /= 10.0;
        }
    } else {
        while (number > DBL_EPSILON) {
            number *= 10.0;
            res = ((uint) number) % 10;
            if (res != 0) break;
        }
    }
    return (res == 9);
}

void task_array(dynamicarray* array) {
    for (size_t i = 0; i < array->size; ++i)
        if (!task_array_check(array->array[i]))
            dynamicarray_remove_at(array, i--);
}

void output_array(dynamicarray* array) {
    printf("Вывод текущего состояния массива\n");
    for (size_t i = 0; i < array->size; ++i) printf("%.*f ", DECIMAL_DIG, array->array[i]);
    printf("\n");
}

bool assert_arraynotempty(dynamicarray *array, void (*func)(dynamicarray*)) {
    if (array == NULL) {
        print_emptyarraywarning();
        return FALSE;
    } else {
        func(array);
        return TRUE;
    }
}

void navigate(dynamicarray* array) {
    bool clearScreen = TRUE;
    MENU_STATE state = main_menu();
    switch (state) {
        case EXIT:
            dynamicarray_free(array);
            return;
        case INITIALIZE:
            if (array != NULL) dynamicarray_free(array);
            array = initialize_array();
            break;
        case INSERTION:
            clearScreen = assert_arraynotempty(array, insertion_array);
            break;
        case DELETION:
            clearScreen = assert_arraynotempty(array, deletion_array);
            break;
        case TASK:
            clearScreen = assert_arraynotempty(array, task_array);
            break;
        case OUTPUT:
            clear_console();
            assert_arraynotempty(array, output_array);
            clearScreen = FALSE;
            break;
        default:
            break;
    }
    if (clearScreen) clear_console();
    navigate(array);
}

int main() {
    init_console();
    navigate(NULL);
    return 0;
}