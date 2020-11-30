//
// Created by meir_ on 11/05/2020.
//

#include <iostream>
#include "CoursesManager.h"
#include "AVLTree.h"
#include "StreamsList.h"




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
    if (courseTree.get(courseID) != nullptr) {
        Course* artist = courseTree.get(courseID);
        for (int i = 0; i < artist->numOfSongs ; ++i) {
            streamsList.deleteArtistSongsTree(artist->songsArray[i], courseID);
        }
        courseTree.remove(courseID);
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType CoursesManager::watchClass(int courseID, int classID) {
    /*std::cout << courseID << " " << lectureID;*/
    if (courseTree.get(courseID) != nullptr) {

        Course* artist = courseTree.get(courseID);


        if(classID >= artist->numOfSongs) return INVALID_INPUT;
        StreamsList::StreamNode *prevNode = artist->songsArray[classID]->prev;

        bool nodeRemoved = false;
        if (streamsList.addStreamToSong(artist->songsArray[classID], classID, courseID, nodeRemoved) == ALLOCATION_ERROR){
            return ALLOCATION_ERROR;
        }
        else {
            artist->songsArray[classID] = (nodeRemoved ? prevNode->next : prevNode->next->next);
            return SUCCESS;
        }
    }
    else return FAILURE;
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


