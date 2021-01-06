
#ifndef BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H
#define BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H


#include "Auxiliaries.h"
#include "RankedAVLTree.h"
#include "HashMap.h"
typedef std::shared_ptr<HashMap<HashMap<RankedAVLNode<int>>>> hash_hash_avl_p;
typedef std::shared_ptr<NodeHash<HashMap<RankedAVLNode<int>>>> nhash_hash_avl_p;
typedef std::shared_ptr<NodeHash<RankedAVLNode<int>>> nhash_avl_p;
typedef std::shared_ptr<HashMap<RankedAVLNode<int>>> hash_avl_p;
typedef std::shared_ptr<RankedAVLNode<int>> avln_p;
class BetterCoursesManager {

    std::shared_ptr<HashMap<HashMap<RankedAVLNode<int>>>> courses_map;
    std::shared_ptr<RankedAVLTree<int>> lectures_tree;


public:

    BetterCoursesManager();

    ~BetterCoursesManager() = default;

    StatusType addCourse(int courseID);

    StatusType removeCourse(int courseID);

    StatusType addClass(int courseID, int *classID);

    StatusType watchClass(int courseID, int classID, int time);

    StatusType timeViewed(int courseID, int classID, int *timeViewed);

    StatusType getIthWatchedClass(int i, int *courseID, int *classID);
};


#endif //BETTERCOURSEMANAGER_BETTERCOURSESMANAGER_H
