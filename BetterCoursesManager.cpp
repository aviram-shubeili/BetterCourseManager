#include "BetterCoursesManager.h"


BetterCoursesManager::BetterCoursesManager() :
        courses_map( hash_hash_avl_p (new HashMap<HashMap<RankedAVLNode<int>>>)),
        lectures_tree(std::shared_ptr<RankedAVLTree<int>>(new RankedAVLTree<int>)) {}



StatusType BetterCoursesManager::addCourse(int courseID) {
    if(isInvalidCourseID(courseID)) {
        return INVALID_INPUT;
    }

    try {
        // create empty lectures map
        hash_avl_p lectures(new HashMap<RankedAVLNode<int>>);
        nhash_hash_avl_p temp = courses_map->insert(courseID);
        // already exists
        if(temp == nullptr) {
            return FAILURE;
        }
        temp->setData(lectures);
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}
StatusType BetterCoursesManager::removeCourse(int courseID) {
    if(isInvalidCourseID(courseID)) {
        return INVALID_INPUT;
    }
    nhash_hash_avl_p course = courses_map->find(courseID);
    if(course == nullptr) {
        return FAILURE;
    }
    hash_avl_p lectures = course->getData();
// TODO: check This (lectures isnt null after deleteNode)
    try {
        // trying to delete node from course map before deleting nodes from tree
        courses_map->deleteNode(courseID);
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    int N = lectures->getUsedCurrentKeys();
    for(int i = 0 ; i < N ; i++) {
        avln_p lecture_node = lectures->find(i)->getData();
        if(lecture_node != nullptr) {
            ThreeKey key = lecture_node->getKey();
            lectures_tree->remove(key);
        }
    }

    return SUCCESS;
}

StatusType BetterCoursesManager::addClass(int courseID, int *classID) {
    if(isInvalidCourseID(courseID)) {
        return INVALID_INPUT;
    }
    nhash_hash_avl_p course = courses_map->find(courseID);
    if(course == nullptr) {
        return FAILURE;
    }
    hash_avl_p lectures = course->getData();
    int class_id = lectures->getUsedCurrentKeys();
    try{
        lectures->insert(class_id);
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    *classID = class_id;
    return SUCCESS;
}

StatusType BetterCoursesManager::watchClass(int courseID, int classID, int time) {
    if(isInvalidCourseID(courseID) or isInvalidClassID(classID) or time <= 0) {
        return INVALID_INPUT;
    }

    nhash_hash_avl_p course = courses_map->find(courseID);
    if(course == nullptr) {
        return FAILURE;
    }
    hash_avl_p lectures = course->getData();
    nhash_avl_p lecture = lectures->find(classID);
    if(lecture == nullptr) {
        // classID +1 > num_classes
        return INVALID_INPUT;
    }
    avln_p lecture_node = lecture->getData();
    ThreeKey key;
    avln_p new_lecture_node;
    // lecture has no views:
    if(lecture_node == nullptr) {
        key = ThreeKey(time,courseID,classID);
        try {
            new_lecture_node = lectures_tree->insert(key, nullptr);
        }
        catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
        }
    }
        // lecture was viewed before:
    else {
        // add time to views
        key = ThreeKey(time + lecture->getData()->getKey().views, courseID, classID);
        try {
            new_lecture_node = lectures_tree->insert(key, nullptr);
        }
        catch (std::bad_alloc&) {
            return ALLOCATION_ERROR;
        }
        // remove old node
        lectures_tree->remove(lecture->getData()->getKey());
    }

    // insert new node to tree and update lectures_map

    lecture->setData(new_lecture_node);

    return SUCCESS;
}

StatusType BetterCoursesManager::timeViewed(int courseID, int classID, int *timeViewed) {
    if(isInvalidCourseID(courseID) or isInvalidClassID(classID)) {
        return INVALID_INPUT;
    }
    nhash_hash_avl_p course = courses_map->find(courseID);
    if(course == nullptr) {
        return FAILURE;
    }
    hash_avl_p lectures = course->getData();
    nhash_avl_p lecture = lectures->find(classID);
    if(lecture == nullptr) {
        // classID +1 > num_classes
        return INVALID_INPUT;
    }
    avln_p lecture_node = lecture->getData();
    if(lecture_node == nullptr) {
        *timeViewed = 0;
    }
    else {
        *timeViewed = lecture_node->getKey().views;
    }
    return SUCCESS;
}

StatusType BetterCoursesManager::getIthWatchedClass(int i, int *courseID, int *classID) {
    if( i <= 0) {
        return INVALID_INPUT;
    }
    try{
        avln_p result = lectures_tree->Select(getRank(lectures_tree->getRoot()) - i + 1);
        *courseID = result->getKey().course_id;
        *classID = result->getKey().class_id;
    }
    catch(InvalidInput&) {
        return FAILURE;
    }

    return SUCCESS;

}
