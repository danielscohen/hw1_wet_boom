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
//    for (int i = zeroTimeLectures.getFirst(); i != -1; i = zeroTimeLectures.getNext()) {
//        std::cout << zeroTimeLectures.getPrev() << " " << zeroTimeLectures.getNext2() << std::endl;
//    }
}

CourseKey::~CourseKey() {
    delete [] lectureArr;
}


