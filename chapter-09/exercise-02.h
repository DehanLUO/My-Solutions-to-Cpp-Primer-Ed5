/*
 * Exercise 9.2: Define a list that holds elements that are deques that hold
 * ints.
 */

#ifndef CHAPTER_09_EXERCISE_02_H_
#define CHAPTER_09_EXERCISE_02_H_

#include <deque>  // std::deque
#include <list>   // std::list

std::list<std::deque<int>> nested_sequence;

#endif  // CHAPTER_09_EXERCISE_02_H_
