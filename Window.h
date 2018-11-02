#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include "Student.h"

class Window {
public:
  Window() : lastIdleTime_(0), totalIdleTime_(0), isOccupied_(false), remainingProcessTime_(0) {}
  ~Window() {}
  // Getters and setters
  int totalIdleTime()        const { return totalIdleTime_; }
  int remainingProcessTime() const { return remainingProcessTime_; }
  bool   isOccupied() const { return isOccupied_; }
  bool & isOccupied()       { return isOccupied_; }

  void passTime(int);
  void receiveStudent(const Student&);
  void display() const;
private:
  int  lastIdleTime_;
  int  totalIdleTime_;
  bool isOccupied_;
  int  remainingProcessTime_;
};

#endif
