#include "ThreeKey.h"


bool ThreeKey::operator==(const ThreeKey &rhs) const {
    return views == rhs.views &&
           course_id == rhs.course_id &&
           class_id == rhs.class_id;
}

bool ThreeKey::operator!=(const ThreeKey &rhs) const {
    return !(rhs == *this);



}

bool ThreeKey::operator<(const ThreeKey &rhs) const {
    if (views < rhs.views)
        return true;
    if (rhs.views < views)
        return false;
    if (course_id > rhs.course_id)
        return true;
    if (rhs.course_id > course_id)
        return false;
    return class_id > rhs.class_id;
}

bool ThreeKey::operator>(const ThreeKey &rhs) const {
    return rhs < *this;
}

std::ostream &operator<<(std::ostream &os, const ThreeKey &to_print) {
    os << to_print.views;
    return os;
}


