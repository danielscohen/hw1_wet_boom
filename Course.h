//
// Created by meir_ on 13/05/2020.
//

#ifndef MUSIC_MANAGER_ARTIST_H
#define MUSIC_MANAGER_ARTIST_H

#include "StreamsList.h"

class Course {

public:

    int numOfSongs;
    StreamsList::StreamNode** songsArray;
    explicit Course(int numOfSongs);
    ~Course();

};

#endif //MUSIC_MANAGER_ARTIST_H
