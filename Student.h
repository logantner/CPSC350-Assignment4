#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>

struct Student {
  int idx;
  int arrivalTime;
  int windowTime;
  bool operator == (const Student& other) const { return idx == other.idx; }
  friend std::ostream& operator << (std::ostream& out, const Student& s) {
    out << "Student" << s.idx;
    return out;
  }
};

#endif
