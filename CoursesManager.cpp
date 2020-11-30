//
// Created by meir_ on 11/05/2020.
//

#include <iostream>
#include "CoursesManager.h"
#include "AVLTree.h"




StatusType CoursesManager::addCourse(int courseID, int numOfClasses) {
    std::shared_ptr<CourseKey> course;
    std::shared_ptr<CourseKey> zeroCourse;
    try {
       course = std::make_shared<CourseKey>(CourseKey(courseID,numOfClasses));
    } catch (...) {return ALLOCATION_ERROR;}

    if(courseTree.isMember(course)) return FAILURE;
    zeroCourse = course;


    try {
        courseTree.insert(course);
        zeroTimeTree.insert(zeroCourse);
    } catch (...) {return ALLOCATION_ERROR;}
    numClasses += numOfClasses;
    return SUCCESS;
}

StatusType CoursesManager::removeCourse(int courseID){
    std::shared_ptr<CourseKey> key;
    std::shared_ptr<CourseKey> course;
    std::shared_ptr<LectureKey> lecture;
    try {
        key = std::make_shared<CourseKey>(CourseKey(courseID,0));
        lecture = std::make_shared<LectureKey>(LectureKey(0, courseID, 0));
    } catch (...) {return ALLOCATION_ERROR;}

    course = courseTree.get(key);
    if(course == nullptr) return FAILURE;

    bool zeroRemoved = false;

    for(int i = 0; i < course->numLectures; i++){
        lecture->lectureID = i;
        lecture->time = course->lectureArr[i];
        if(course->lectureArr[i] > 0) lectureTree.remove(lecture);
        else if (!zeroRemoved) {
            zeroTimeTree.remove(course);
            zeroRemoved = true;
        }

    }

    numClasses -= course->numLectures;

    courseTree.remove(course);


    return SUCCESS;

}

StatusType CoursesManager::watchClass(int courseID, int classID, int time) {
    std::shared_ptr<CourseKey> course;
    std::shared_ptr<CourseKey> key;
    std::shared_ptr<LectureKey> lecture;
    try {
        key = std::make_shared<CourseKey>(CourseKey(courseID,0));
        lecture = std::make_shared<LectureKey>(LectureKey(classID, courseID, time));
    } catch (...) {return ALLOCATION_ERROR;}

    course = courseTree.get(key);
    if(course == nullptr) return FAILURE;

    if(classID + 1 > course->numLectures) return INVALID_INPUT;

    if(course->lectureArr[classID] == 0) {
        course->zeroTimeLectures.remove(classID);
        if(course->zeroTimeLectures.isEmpty) zeroTimeTree.remove(course);
        lectureTree.insert(lecture);
        course->lectureArr[classID] = time;
    } else {
        lecture->time = course->lectureArr[classID];
        lectureTree.remove(lecture);
        time += course->lectureArr[classID];
        course->lectureArr[classID] = time;
        lecture->time = time;
        lectureTree.insert(lecture);
    }


    return SUCCESS;
}

StatusType CoursesManager::timeViewed (int courseID, int classID, int* timeViewed){
    std::shared_ptr<CourseKey> course;
    std::shared_ptr<CourseKey> key;
    try {
        key = std::make_shared<CourseKey>(CourseKey(courseID,0));
    } catch (...) {return ALLOCATION_ERROR;}

    course = courseTree.get(key);
    if(course == nullptr) return FAILURE;

    if(classID + 1 > course->numLectures) return INVALID_INPUT;

    *timeViewed = course->lectureArr[classID];
    return SUCCESS;
}

StatusType CoursesManager::getMostViewedClasses (int numOfClasses, int *courses, int *classes){
    if(numOfClasses > numClasses) return FAILURE;
    int count = 0;
    for (std::shared_ptr<LectureKey> lecture = lectureTree.getFirst(); lecture != nullptr; lecture = lectureTree.getNext()) {
        courses[count] = lecture->courseID;
        classes[count] = lecture->lectureID;
        count++;
        if(count == numOfClasses) return SUCCESS;
    }

    for (std::shared_ptr<CourseKey> course = zeroTimeTree.getFirst(); course != nullptr; course = zeroTimeTree.getNext()) {
        for (int i = course->zeroTimeLectures.getFirst(); i != -1; i = course->zeroTimeLectures.getNext()) {
            courses[count] = course->courseID;
            classes[count] = i;
            count++;
            if(count == numOfClasses) return SUCCESS;
        }
    }


    return SUCCESS;
}


