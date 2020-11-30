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

StatusType CoursesManager::watchClass(int courseID, int classID) {
    std::shared_ptr<CourseKey> course;
    std::shared_ptr<CourseKey> key;
    try {
        key = std::make_shared<CourseKey>(CourseKey(courseID,0));
    } catch (...) {return ALLOCATION_ERROR;}

    course = courseTree.get(key);
    if(course == nullptr) return FAILURE;

    if(classID + 1 > course->numLectures) return INVALID_INPUT;

    if(course->lectureArr[classID] == 0) {

    }


    try {
        courseTree.insert(course);
        zeroTimeTree.insert(zeroCourse);
    } catch (...) {return ALLOCATION_ERROR;}
    numClasses += numOfClasses;
    return SUCCESS;
}

StatusType CoursesManager::timeViewed (int artistID, int songID, int* streams){
    if (courseTree.get(artistID) != nullptr) {
        Course* artist = courseTree.get(artistID);
        if(songID >= artist->numOfSongs) return INVALID_INPUT;
        *streams = (artist->songsArray[songID]->numStreams); // dereference ok?
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType CoursesManager::getMostViewedClasses (int numOfSongs, int *artists, int *songs){
    return streamsList.getRecommendedSongs(numOfSongs, artists, songs);
}


