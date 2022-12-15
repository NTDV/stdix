//
// Created by Danila Valkovets (dahnh33@gmail.com) on 12.11.2022.
//
#include "stdix_test.h" //todo Add test

int compare_students_fullname(const void* a, const void* b) {
    const STUDENT* left = *(const void * const *)a;
    const STUDENT* right = *(const void * const *)b;
    return strcmp(left->fullName, right->fullName);
}

int compare_students_group(const void* a, const void* b) {
    const STUDENT* left = *(const void * const *)a;
    const STUDENT* right = *(const void * const *)b;
    return strncmp(left->group, right->group, sizeof(right->group) / sizeof(right->group[0]));
}

int compare_students_mark(const void* a, const void* b) {
    const STUDENT* left = *(const void * const *)a;
    const STUDENT* right = *(const void * const *)b;
    return (left->averageMark > right->averageMark) - (left->averageMark < right->averageMark);
}

int compare_students_fullname_back(const void* a, const void* b) {
    return -1 * compare_students_fullname(a, b);
}

int compare_students_group_back(const void* a, const void* b) {
    return -1 * compare_students_group(a, b);
}

int compare_students_mark_back(const void* a, const void* b) {
    return -1 * compare_students_mark(a, b);
}

void choose_sort(dynamicarray* array, OPTION_PROGRAM_STATE* state) {
    COMPARATOR comparatorMapping[3][2]; // Algorithm -> Property -> Direction
    comparatorMapping[FULL_NAME][FORWARD] = &compare_students_fullname;
    comparatorMapping[FULL_NAME][BACKWARD] = &compare_students_fullname_back;
    comparatorMapping[FULL_GROUP][FORWARD] = &compare_students_group;
    comparatorMapping[FULL_GROUP][BACKWARD] = &compare_students_group_back;
    comparatorMapping[AVERAGE_MARK][FORWARD] = &compare_students_mark;
    comparatorMapping[AVERAGE_MARK][BACKWARD] = &compare_students_mark_back;

    SORTER algorithmMapping[3];
    algorithmMapping[QUICK_LIB] = &qsort;
    algorithmMapping[QUICK_OWN] = &ix_qsort;
    algorithmMapping[PAIR_INS] = &ix_pairinsertion_sort;
    dynamicarray_sort(array, algorithmMapping[state->sortAlgorithm], comparatorMapping[state->sortProperty][state->sortDirection]);
}

int main(int argc, char **argv) {
    init_console();
    OPTION_TYPE option;
    OPTION_PROGRAM_STATE* state = malloc(sizeof *state);
    state->outputPath = NULL;

    while ((option = getopt(argc, argv, "a:p:d:i:o:")) != -1) {
        switch (option) {
            case ALGORITHM:
                if (strcmp("0", optarg) == 0) state->sortAlgorithm = QUICK_LIB;
                else if (strcmp("1", optarg) == 0) state->sortAlgorithm = QUICK_OWN;
                else if (strcmp("2", optarg) == 0) state->sortAlgorithm = PAIR_INS;
                else goto ARGS_ERROR;
                break;
            case PROPERTY:
                if (strcmp("0", optarg) == 0) state->sortProperty = FULL_NAME;
                else if (strcmp("1", optarg) == 0) state->sortProperty = FULL_GROUP;
                else if (strcmp("2", optarg) == 0) state->sortProperty = AVERAGE_MARK;
                else goto ARGS_ERROR;
                break;
            case DIRECTION:
                if (strcmp("0", optarg) == 0) state->sortDirection = FORWARD;
                else if (strcmp("1", optarg) == 0) state->sortDirection = BACKWARD;
                else goto ARGS_ERROR;
                break;
            case IN:
                if (access(optarg, F_OK) == 0) state->inputPath = optarg;
                else goto ARGS_ERROR;
                break;
            case OUT:
                state->outputPath = optarg;
                break;
            case ERROR:
            default:
                goto ARGS_ERROR;
                break;
        }
    }

    if (state->outputPath == NULL) {
        ARGS_ERROR:
        perror("Error with some values!\n");
        return 0;
    }

    dynamicarray* array = dynamicarray_init();
    FILE* input = fopen(state->inputPath, "r");
    ix_string* line;
    while ((line = ix_string_readline_stream(input)) != NULL) {
        string token = strtok(line->chars, ";");
        STUDENT* student = malloc(sizeof *student);
        const size_t groupLength = sizeof(student->group) / sizeof(student->group[0]);
        short validator_counter = 0;
        while(token != NULL) {
            if (++validator_counter > 3) break;
            switch (validator_counter) {
                case 1:
                    student->fullName = token;
                    break;
                case 2:
                    if (strlen(token) == groupLength)
                        for (size_t i = 0; i < groupLength; ++i)
                            student->group[i] = token[i];
                    else goto ARGS_ERROR;
                    break;
                case 3:
                    student->averageMark = strtof(token, NULL);
                    break;
                default:
                    goto ARGS_ERROR;
                    break;
            }
            token = strtok(NULL, ";");
        }
        if (validator_counter == 3) dynamicarray_insert_at(array, array->size, student);
        free(line);
    }
    free(line);
    fclose(input);

#ifndef TIMING
    choose_sort(array, state);
#endif
#ifdef TIMING
    clock_t clck = clock();
    choose_sort(array, state);
    clck = clock() - clck;
    //double timer = ((double)clck) / CLOCKS_PER_SEC * 1000 * 1000;
    printf("Elapsed time: %ld us\n", clck);
#endif

    FILE* output = fopen(state->outputPath, "w");
    if (output == NULL) goto ARGS_ERROR;
    for (size_t i = 0; i < array->size; ++i) {
        STUDENT* student = array->array[i];
        fprintf(output, "%s;%.*s;%.1f\n", student->fullName, (int)(sizeof(student->group) / sizeof(student->group[0])), student->group, student->averageMark);
        free(student->fullName);
        free(student);
    }
    fclose(output);
    free(state);
    dynamicarray_free(array);
    return 0;
}