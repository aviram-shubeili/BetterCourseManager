#include"library2.h"
#include"BetterCoursesManager.h"
#include <exception>
void *Init() {
    BetterCoursesManager *DS;
    try {
        DS = new BetterCoursesManager ();
    } catch (std::bad_alloc&) {
        return nullptr;
    }
    return (void*)DS;
}

StatusType AddCourse(void* DS, int courseID) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType) (((BetterCoursesManager *)DS)-> addCourse(courseID));
}

StatusType RemoveCourse(void *DS, int courseID) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType) ((BetterCoursesManager*) DS)-> removeCourse(courseID);
}


StatusType AddClass(void* DS, int courseID, int* classID) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType) (((BetterCoursesManager *)DS)-> addClass(courseID, classID));
}


StatusType WatchClass(void *DS, int courseID, int classID, int time) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType)((BetterCoursesManager*) DS)-> watchClass(courseID, classID, time);
}


StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType)((BetterCoursesManager*) DS)-> timeViewed(courseID, classID, timeViewed);
}




StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID) {
    if(DS == nullptr) return INVALID_INPUT;

    return (StatusType)((BetterCoursesManager*) DS)-> getIthWatchedClass(i, courseID, classID);
}

void Quit(void **DS) {
    if(*DS != nullptr) {
        delete ((BetterCoursesManager*) *DS);
    }
    *DS = nullptr;
}
