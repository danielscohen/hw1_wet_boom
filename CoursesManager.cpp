//
// Created by meir_ on 11/05/2020.
//

#include <iostream>
#include "CoursesManager.h"
#include "AVLTree.h"
#include "StreamsList.h"




StatusType CoursesManager::addData(int courseID, int numOfSongs) {
    if (courseTree.get(courseID) == nullptr) {
        Course* course;
        try {
            course = new Course(numOfSongs);
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



        if (streamsList.addArtistSongs(numOfSongs, courseID) == ALLOCATION_ERROR){
            courseTree.remove(courseID);
            return ALLOCATION_ERROR;
        }
        else {
            for (int i = 0; i < numOfSongs ; ++i) {
                course->songsArray[i] = streamsList.getZeroStreams();
            }
            return SUCCESS;
        }
    }
    else return FAILURE;
}

StatusType CoursesManager::removeData(int artistID){
    if (courseTree.get(artistID) != nullptr) {
        Course* artist = courseTree.get(artistID);
        for (int i = 0; i < artist->numOfSongs ; ++i) {
            streamsList.deleteArtistSongsTree(artist->songsArray[i], artistID);
        }
        courseTree.remove(artistID);
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType CoursesManager::addToSongCount(int artistID, int songID) {
    /*std::cout << courseID << " " << lectureID;*/
    if (courseTree.get(artistID) != nullptr) {

        Course* artist = courseTree.get(artistID);


        if(songID >= artist->numOfSongs) return INVALID_INPUT;
        StreamsList::StreamNode *prevNode = artist->songsArray[songID]->prev;

        bool nodeRemoved = false;
        if (streamsList.addStreamToSong(artist->songsArray[songID], songID, artistID, nodeRemoved)==ALLOCATION_ERROR){
            return ALLOCATION_ERROR;
        }
        else {
            artist->songsArray[songID] = (nodeRemoved ? prevNode->next : prevNode->next->next);
            return SUCCESS;
        }
    }
    else return FAILURE;
}

StatusType CoursesManager::getNumOfStreams (int artistID, int songID, int* streams){
    if (courseTree.get(artistID) != nullptr) {
        Course* artist = courseTree.get(artistID);
        if(songID >= artist->numOfSongs) return INVALID_INPUT;
        *streams = (artist->songsArray[songID]->numStreams); // dereference ok?
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType CoursesManager::getRecommendedSongs (int numOfSongs, int *artists, int *songs){
    return streamsList.getRecommendedSongs(numOfSongs, artists, songs);
}


