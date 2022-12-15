//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//
#ifndef STDIX_TEST_H
#define STDIX_TEST_H

#include <string.h>
#include "../src/stdix_string.h"
#include "../src/stdix_dynamicarray.h"
#include "../src/stdix_sorting.h"
#include <getopt.h>
#include <string.h>
#include <unistd.h>

#define TIMING
#ifdef TIMING
#include <time.h>
#endif

typedef enum {
    ALGORITHM = 'a',
    PROPERTY = 'p',
    DIRECTION = 'd',
    IN = 'i',
    OUT = 'o',

    ERROR = '?'
} OPTION_TYPE;

typedef enum {
    QUICK_LIB = NORMILIZE_CHAR_FOR_INDEXING('0'),
    QUICK_OWN = NORMILIZE_CHAR_FOR_INDEXING('1'),
    PAIR_INS = NORMILIZE_CHAR_FOR_INDEXING('2')
} OPTION_SORT_ALGORITHM;

typedef enum {
    FULL_NAME = NORMILIZE_CHAR_FOR_INDEXING('0'),
    FULL_GROUP = NORMILIZE_CHAR_FOR_INDEXING('1'),
    AVERAGE_MARK = NORMILIZE_CHAR_FOR_INDEXING('2')
} OPTION_SORT_PROPERTY;

typedef enum {
    FORWARD = NORMILIZE_CHAR_FOR_INDEXING('0'),
    BACKWARD = NORMILIZE_CHAR_FOR_INDEXING('1')
} OPTION_SORT_DIRECTION;

typedef struct {
    OPTION_SORT_ALGORITHM sortAlgorithm;
    OPTION_SORT_PROPERTY sortProperty;
    OPTION_SORT_DIRECTION sortDirection;

    string inputPath;
    string outputPath;
} OPTION_PROGRAM_STATE;

#endif //STDIX_TEST_H
