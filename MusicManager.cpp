//
// Created by meir_ on 11/05/2020.
//

#include <iostream>
#include "MusicManager.h"
#include "AVLTree.h"
#include "StreamsList.h"




StatusType MusicManager::addData(int artistID, int numOfSongs) {
    if (artistTree.get(artistID) == nullptr) {
        Artist* artist;
        try {
            artist = new Artist(numOfSongs);
            try {
                artistTree.insert(artistID, artist);
            }
            catch (...){
                delete artist;
                throw;
            }
        }
        catch (...){
            return ALLOCATION_ERROR;
        }



        if (streamsList.addArtistSongs(numOfSongs, artistID) == ALLOCATION_ERROR){
            artistTree.remove(artistID);
            return ALLOCATION_ERROR;
        }
        else {
            for (int i = 0; i < numOfSongs ; ++i) {
                artist->songsArray[i] = streamsList.getZeroStreams();
            }
            return SUCCESS;
        }
    }
    else return FAILURE;
}

StatusType MusicManager::removeData(int artistID){
    if (artistTree.get(artistID)!= nullptr) {
        Artist* artist = artistTree.get(artistID);
        for (int i = 0; i < artist->numOfSongs ; ++i) {
            streamsList.deleteArtistSongsTree(artist->songsArray[i], artistID);
        }
        artistTree.remove(artistID);
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    /*std::cout << artistID << " " << songID;*/
    if (artistTree.get(artistID)!= nullptr) {

        Artist* artist = artistTree.get(artistID);


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

StatusType MusicManager::getNumOfStreams (int artistID, int songID, int* streams){
    if (artistTree.get(artistID)!= nullptr) {
        Artist* artist = artistTree.get(artistID);
        if(songID >= artist->numOfSongs) return INVALID_INPUT;
        *streams = (artist->songsArray[songID]->numStreams); // dereference ok?
        return SUCCESS;
    }
    else return FAILURE;
}

StatusType MusicManager::getRecommendedSongs (int numOfSongs, int *artists, int *songs){
    return streamsList.getRecommendedSongs(numOfSongs, artists, songs);
}


