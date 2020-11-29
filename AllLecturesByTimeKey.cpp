//
// Created by dcohe on 11/06/2020.
//

#include "AllLecturesByTimeKey.h"

bool operator<(const AllLecturesByTimeKey &lhs, const AllLecturesByTimeKey &rhs) {
    if(lhs.time > rhs.time) return true;
    if(lhs.time < rhs.time) return false;
    if(lhs.courseID < rhs.courseID) return true;
    if(lhs.courseID > rhs.courseID) return false;
    return lhs.lectureID < rhs.lectureID;
}

bool operator==(const AllLecturesByTimeKey &lhs, const AllLecturesByTimeKey &rhs) {
    return lhs.courseID == rhs.courseID && lhs.lectureID == rhs.lectureID;
}

bool operator>(const AllLecturesByTimeKey &lhs, const AllLecturesByTimeKey &rhs) {
    return rhs < lhs;
}

bool operator!=(const AllLecturesByTimeKey &lhs, const AllLecturesByTimeKey &rhs) {
    return !(lhs == rhs);
}

AllLecturesByTimeKey::AllLecturesByTimeKey(int songId, int artistId, int numStreams) : lectureID(songId),
                                                                                       courseID(artistId),
                                                                                       time(numStreams) {}


