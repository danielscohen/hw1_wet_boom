//
// Created by dcohe on 30/11/2020.
//
#include "library.h"
#include "CoursesManager.h"


void *Init() {
    CoursesManager *DS = new CoursesManager();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID, int numOfClasses) {
    if(DS == nullptr || courseID <= 0 || numOfClasses <= 0) return INVALID_INPUT;
    return ((CoursesManager *)DS)->addCourse(courseID, numOfClasses);
}

StatusType RemoveCourse(void *DS, int courseID) {
    if(DS == nullptr || courseID <= 0) return INVALID_INPUT;
    return ((CoursesManager *)DS)->removeCourse(courseID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time) {
    if(DS == nullptr || courseID <= 0 || classID < 0 || time <= 0) return INVALID_INPUT;
    return ((CoursesManager *)DS)->watchClass(courseID, classID, time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed) {
    if(DS == nullptr || courseID <= 0 || classID < 0) return INVALID_INPUT;
    return ((CoursesManager *)DS)->timeViewed(courseID, classID, timeViewed);
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes) {
    if(DS == nullptr || numOfClasses <= 0) return INVALID_INPUT;
    return ((CoursesManager *)DS)->getMostViewedClasses(numOfClasses, courses, classes);
}

void Quit(void **DS) {
    delete ((CoursesManager*)*DS);
    *DS = nullptr;
}
