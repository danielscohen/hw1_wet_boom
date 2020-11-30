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

CourseKey::CourseKey(int courseId, int numLec) : courseID(courseId), numLectures(numLec), lectureArr(new int[numLec]()) {
   for(int i = 0; i < numLec; i++) zeroTimeLectures.add(i);
}

CourseKey::~CourseKey() {
    delete [] lectureArr;
}


