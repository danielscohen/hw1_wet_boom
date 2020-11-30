//
// Created by meir_ on 11/05/2020.
//

#ifndef MUSIC_MANAGER_MUSICMANAGER_H
#define MUSIC_MANAGER_MUSICMANAGER_H

#include <memory>
#include "LectureKey.h"
#include "AVLTree.h"
#include "CourseKey.h"

/**
 * to erase
 */



class CoursesManager {

    AVLTree<std::shared_ptr<LectureKey>> lectureTree;
    AVLTree<std::shared_ptr<CourseKey>> courseTree;
    AVLTree<std::shared_ptr<CourseKey>> zeroTimeTree;
    int numClasses;


public:


    StatusType addCourse(int courseID, int numOfClasses);

    StatusType removeCourse(int courseID);

    StatusType watchClass(int courseID, int classID, int time);

    StatusType timeViewed (int courseID, int classID, int* timeViewed);

    StatusType getMostViewedClasses (int numOfClasses, int *courses, int *classes);

};













#endif //MUSIC_MANAGER_MUSICMANAGER_H

