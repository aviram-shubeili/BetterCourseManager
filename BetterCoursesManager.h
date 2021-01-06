
#ifndef BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H
#define BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H


#include "Auxiliaries.h"

class BetterCoursesManager {
int s;
public:
    StatusType addCourse(int courseID);

    StatusType removeCourse(int courseID);

    StatusType addClass(int courseID, int *classID);

    StatusType watchClass(int courseID, int classID, int time);

    StatusType timeViewed(int courseID, int classID, int *timeViewed);

    StatusType getIthWatchedClass(int i, int *courseID, int *classID);
};


#endif //BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H
