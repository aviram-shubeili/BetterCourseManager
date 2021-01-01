#ifndef BETTERCOURSEMANAGER_THREEKEY_H
#define BETTERCOURSEMANAGER_THREEKEY_H
#include <iostream>

class ThreeKey {

public:
    int views;
    int course_id;
    int class_id;

    ThreeKey(int views, int course_id, int class_id) :
            views(views), course_id(course_id), class_id(class_id) {}

    ThreeKey(int single_key) :
            views(single_key), course_id(-1), class_id(-1)  {}


    bool operator<(const ThreeKey &rhs) const;

    bool operator>(const ThreeKey &rhs) const;

    bool operator==(const ThreeKey &rhs) const;

    bool operator!=(const ThreeKey &rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const ThreeKey& to_print);

};


#endif //BETTERCOURSEMANAGER_THREEKEY_H
