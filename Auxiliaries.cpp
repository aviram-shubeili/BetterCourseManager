//
// Created by avira on 29/11/2020.
//

#include "Auxiliaries.h"

bool isInvalidCourseID(int key) {
    return key <= 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

bool isInvalidClassID(int key) {
    return key < 0;
}
