cmake_minimum_required(VERSION 3.15)
project(hw1_wet_boom)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw1_wet_boom main.cpp Course.cpp AVLTree.cpp CoursesManager.cpp Song.cpp StreamsList.cpp library.h LectureKey.cpp
        CourseKey.cpp List.cpp)