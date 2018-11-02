#ifndef _OFFICE_H_
#define _OFFICE_H_

#include "DoubleLinkedList.h"
#include "Window.h"
#include "Student.h"

class Office {
public:
  Office() : numWindows_(0) { windows_ = new Window[0]; }
  Office(int);
  // Rule of three methods
  ~Office() { delete[] windows_; }
  Office(const Office& other) { copy(other); }
  Office& operator = (const Office& other) { copy(other); return *this; }
  // Getters, Setters
  int numWindows() const { return numWindows_; }
  int idleTime(int winIdx) const { return windows_[winIdx].totalIdleTime(); }
  DoubleLinkedList<int> & waitingTimes() { return waitingTimes_; }
  // Supprt functions
  int minWindowTime() const;
  int maxWindowTime() const;
  void passTime(int);
  void pairStudentWithWindow(const Student&, int);
  bool availableWindow() const;
  // Aesthetics
  void display() const;
private:
  int numWindows_;
  Window* windows_;
  DoubleLinkedList<int> waitingTimes_;
  void copy(const Office&);
};

#endif
