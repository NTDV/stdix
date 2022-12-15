//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.12.2022.
//

#include "stdix_sorting.h"

void swap(void* a, void* b, size_t size) {
    char buffer[size];
    memcpy(buffer, a, size);
    memcpy(a, b, size);
    memcpy(b, buffer, size);
}

void dynamicarray_sort(dynamicarray* array, SORTER algorithm, COMPARATOR comparator) {
    algorithm(array->array, array->size, sizeof *(array->array), comparator);
}

size_t place_pivot(void* base, size_t low, size_t high, size_t size, COMPARATOR comparator) {
    size_t pivot = low;
    size_t switch_i = low + 1;
    char* array_ptr = (char *) base;
    for (size_t i = switch_i; i <= high; ++i) {
        if (comparator(array_ptr + i * size, array_ptr + pivot * size) < 0) {
            swap(array_ptr + i * size, array_ptr + switch_i * size, size);
            swap(array_ptr + pivot * size, array_ptr + switch_i * size, size);
            ++pivot;
            ++switch_i;
        }
    }
    return pivot;
}

void ix_qsort_(void* base, size_t low, size_t high, size_t size, COMPARATOR comparator) {
    if (low >= high) return;
    size_t pivot = place_pivot(base, low, high, size, comparator);
    if (pivot > 0) ix_qsort_(base, low, pivot - 1, size, comparator);
    ix_qsort_(base, pivot + 1, high, size, comparator);
}

void ix_qsort(void* base, size_t length, size_t size, COMPARATOR comparator) {
    ix_qsort_(base, 0, length - 1, size, comparator);
}

void ix_pairinsertion_sort(void* base, size_t length, size_t size, COMPARATOR comparator) {
    size_t left = 1;
    size_t right = length - 1;
    STUDENT** a = (STUDENT **) base;
    for (size_t k = left; ++left <= right; k = ++left) {
        STUDENT* a1 = a[k];
        STUDENT* a2 = a[left];
        if (comparator(&a1, &a2) < 0) {
            a2 = a1;
            a1 = a[left];
        }
        while (k != 0 && comparator(&a1, &a[--k]) < 0) a[k + 2] = a[k];
        if (comparator(&a1, &a[k])) a[k + 2] = a[k];
        a[++k + 1] = a1;
        while (k != 0 && comparator(&a2, &a[--k]) < 0) a[k + 1] = a[k];
        if (comparator(&a1, &a[k])) a[k + 1] = a[k];
        a[k + 1] = a2;
    }

    STUDENT* last = a[right];
    while (right != 0 && comparator(&last, &a[--right]) < 0) a[right + 1] = a[right];
    if (comparator(&last, &a[right]) < 0) a[right + 1] = a[right];
    a[right + 1] = last;

    /*
    STUDENT* pin = array[right];
    for (size_t i, p = right; ++left < right;) {
        STUDENT* ai = array[i = left];

        if (comparator(&ai, &array[i - 1]) < 0) {
            array[i] = array[--i];
            while (comparator(&ai, &array[--i]) < 0) array[i + 1] = array[i];
            array[i + 1] = ai;
        } else if (p > i && ai > pin) {
            while (comparator(&array[--p], &pin) > 0);
            if (p > i) {
                ai = array[p];
                array[p] = array[i];
            }

            while (comparator(&ai, &array[--i]) < 0) array[i + 1] = array[i];
            array[i + 1] = ai;
        }
    }

    for (size_t i; left < right; ++left) {
        STUDENT* a1 = array[i = left];
        STUDENT* a2 = array[++left];

        if (comparator(&a1, &a2) > 0) {
            while (comparator(&a1, &array[--i]) < 0) array[i + 2] = array[i];
            array[++i + 1] = a1;
            while (comparator(&a2, &array[--i]) < 0) array[i + 1] = array[i];
            array[i + 1] = a2;
        } else if (comparator(&a1, &array[i - 1]) < 0) {
            while (comparator(&a2, &array[--i]) < 0) array[i + 2] = array[i];
            array[++i + 1] = a2;
            while (comparator(&a1, &array[--i]) < 0) array[i + 1] = array[i];
            array[i + 1] = a1;
        }
    }
     */
}