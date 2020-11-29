//
// Created by meir_ on 11/05/2020.
//

#ifndef MUSIC_MANAGER_MUSICMANAGER_H
#define MUSIC_MANAGER_MUSICMANAGER_H

#include <memory>
#include "Course.h"
#include "StreamsList.h"
#include "LectureKey.h"

/**
 * to erase
 */



class CoursesManager {

    AVLTree<std::shared_ptr<LectureKey>> lectureTree;
    AVLTree<std::shared_ptr<CourseKey>> courseTree;
    StreamsList streamsList;


public:


    StatusType addData(int courseID, int numOfSongs);

    StatusType removeData(int artistID);

    StatusType addToSongCount(int artistID, int songID);

    StatusType getNumOfStreams (int artistID, int songID, int* streams);

    StatusType getRecommendedSongs (int numOfSongs, int *artists, int *songs);

};













#endif //MUSIC_MANAGER_MUSICMANAGER_H

