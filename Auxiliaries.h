
#ifndef BOOM_AUXILIARIES_H
#define BOOM_AUXILIARIES_H

#include <memory>
#include "BoomExceptions.h"
#include "library2.h"
#include <cassert>
#include <iostream>
#include "ThreeKey.h"


/**
 * return true if key <= 0, false otherwise
 * @param key
 * @return
 */
bool isInvalidCourseID(int key);
/**
 * return true if key < 0, false otherwise
 * @param key
 * @return
 */
bool isInvalidClassID(int key);


int max(int a,int b);

#endif //BOOM_AUXILIARIES_H
