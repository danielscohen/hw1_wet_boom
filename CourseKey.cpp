//
// Created by dcohe on 11/06/2020.
//

#include "CourseKey.h"

bool operator<(const CourseKey &lhs, const CourseKey &rhs) {
    return lhs.courseID < rhs.courseID;
}

bool operator==(const CourseKey &lhs, const CourseKey &rhs) {
    return lhs.courseID == rhs.courseID;
}

bool operator>(const CourseKey &lhs, const CourseKey &rhs) {
    return rhs < lhs;
}

bool operator!=(const CourseKey &lhs, const CourseKey &rhs) {
    return !(lhs == rhs);
}

CourseKey::CourseKey(int courseId, int numLec) : courseID(courseId), numLectures(numLec),
    zeroTimeLectures(numLec), lectureArr(new int[numLec]()) {
}

CourseKey::~CourseKey() {
    delete [] lectureArr;
}


