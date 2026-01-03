#pragma once
#include "game.h"
#include <stdio.h>

extern int tests_run;
extern int tests_passed;

#define ASSERT(test, message)                                                                      \
    do {                                                                                           \
        tests_run++;                                                                               \
        if (!(test)) {                                                                             \
            printf("FAIL: %s\n", message);                                                         \
            return 0;                                                                              \
        } else {                                                                                   \
            tests_passed++;                                                                        \
        }                                                                                          \
    } while (0)

static bool pieces_match(Piece *p1, Piece *p2) {
    if (p1 == NULL) {
        return false;
    };

    if (p2 == NULL) {
        return false;
    };

    if (p1->color != p2->color) {
        return false;
    }

    if (p1->unittype != p2->unittype) {
        return false;
    }

    return true;
};
