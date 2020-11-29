//
// Created by meir_ on 11/05/2020.
//

#ifndef MUSIC_MANAGER_MUSICMANAGER_H
#define MUSIC_MANAGER_MUSICMANAGER_H

#include "Course.h"
#include "StreamsList.h"
/**
 * to erase
 */
typedef int Song;



class CoursesManager {

    AVLTree<Course> courseTree;
    StreamsList streamsList;


public:


    StatusType addData(int courseID, int numOfSongs);

    StatusType removeData(int artistID);

    StatusType addToSongCount(int artistID, int songID);

    StatusType getNumOfStreams (int artistID, int songID, int* streams);

    StatusType getRecommendedSongs (int numOfSongs, int *artists, int *songs);

};













#endif //MUSIC_MANAGER_MUSICMANAGER_H

