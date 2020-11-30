//
// Created by dcohe on 11/06/2020.
//

#include "LectureKey.h"

bool operator<(const LectureKey &lhs, const LectureKey &rhs) {
    if(lhs.time > rhs.time) return true;
    if(lhs.time < rhs.time) return false;
    if(lhs.courseID < rhs.courseID) return true;
    if(lhs.courseID > rhs.courseID) return false;
    return lhs.lectureID < rhs.lectureID;
}

bool operator==(const LectureKey &lhs, const LectureKey &rhs) {
    return lhs.courseID == rhs.courseID && lhs.lectureID == rhs.lectureID;
}

bool operator>(const LectureKey &lhs, const LectureKey &rhs) {
    return rhs < lhs;
}

bool operator!=(const LectureKey &lhs, const LectureKey &rhs) {
    return !(lhs == rhs);
}

LectureKey::LectureKey(int lectureID, int courseID, int time) : lectureID(lectureID),
                                                                courseID(courseID),
                                                                time(time) {}


