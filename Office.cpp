#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Office.h"
#include "Window.h"
#include "DoubleLinkedList.h"

Office::Office(int n) : numWindows_(n) {
  windows_ = new Window[numWindows_];
  for (int i=0; i<numWindows_; ++i) {
    windows_[i] = Window();
  }
}

int Office::minWindowTime() const {
  // Returns the least amount of remaining process time across all windows
  int minTime = windows_[0].remainingProcessTime();
  for (int i=0; i<numWindows_; ++i) {
    minTime = std::min(minTime, windows_[i].remainingProcessTime());
  }
  return minTime;
}

int Office::maxWindowTime() const {
  // Returns the greatest amount of remaining process time across all windows
  int maxTime = 0;
  for (int i=0; i<numWindows_; ++i) {
    maxTime = std::max(maxTime, windows_[i].remainingProcessTime());
  }
  return maxTime;
}

void Office::passTime(int timeToPass) {
  // Passes time for each of the windows
  for (int i=0; i<numWindows_; ++i) {
    windows_[i].passTime(timeToPass);
  }
}

void Office::pairStudentWithWindow(const Student& student, int currentTime) {
  // Finds a free window and assigns the provided student to it
  // Also records the amount of time the student has been waiting in the queue
  // This method should only be called if free windows are available. Throws
  // an exception otherwise
  for (int i=0; i<numWindows_; ++i) {
    if ( !windows_[i].isOccupied() ) {
      windows_[i].receiveStudent(student);
      waitingTimes_.insertBack(currentTime - student.arrivalTime);
      return;
    }
  }
  throw std::runtime_error("No free window while attempting to assign student");
}

bool Office::availableWindow() const {
  // Returns true if at least one window is not currently occupied
  for (int i=0; i<numWindows_; ++i) {
    if ( !windows_[i].isOccupied() ) { return true; }
  }
  return false;
}

void Office::display() const {
  for (int i=0; i<numWindows_; ++i) {
    std::cout << "Window " << i << ": ";
    windows_[i].display();
  }
}

void Office::copy(const Office& other) {
  // Performs a deep copy of other onto the current object
  numWindows_ = other.numWindows_;
  waitingTimes_ = other.waitingTimes_;
  delete[] windows_;
  windows_ = new Window[numWindows_];
  for (int i=0; i<numWindows_; ++i) {
    windows_[i] = other.windows_[i];
  }
}
