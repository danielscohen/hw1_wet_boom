//
// Created by meir_ on 11/05/2020.
//

#include <iostream>
#include "CoursesManager.h"
#include "AVLTree.h"
#include "StreamsList.h"




StatusType CoursesManager::addCourse(int courseID, int numOfSongs) {
    if (courseTree.get(courseID) == nullptr) {
        Course* course;
        try {
            course = new Course(numOfClasses);
            try {
                courseTree.insert(courseID, course);
            }
            catch (...){
                delete course;
                throw;
            }
        }
        catch (...){
            return ALLOCATION_ERROR;
        }



        if (streamsList.addArtistSongs(numOfClasses, courseID) == ALLOCATION_ERROR){
            courseTree.remove(courseID);
            return ALLOCATION_ERROR;
        }
        else {
            for (int i = 0; i < numOfClasses ; ++i) {
                course->songsArray[i] = streamsList.getZeroStreams();
            }
            return SUCCESS;
        }
    }
    else return FAILURE;
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


