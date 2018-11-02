#include <iostream>
#include "Window.h"

void Window::passTime(int timeToPass) {
  // Updates the window's remaining process time and total idle time, whichever
  // is relevant for the window
  if ( !isOccupied_ ) {
    totalIdleTime_ += timeToPass;
  }
  else if ( remainingProcessTime_ > timeToPass ) {
    remainingProcessTime_ -= timeToPass;
  }
  else {
    totalIdleTime_ += timeToPass - remainingProcessTime_;
    remainingProcessTime_ = 0;
    isOccupied_ = false;
  }
}

void Window::receiveStudent(const Student& student) {
  // Sets status to occupied and updates remaining process time
  isOccupied_ = true;
  remainingProcessTime_ = student.windowTime;
}

void Window::display() const {
  if (isOccupied_) {
    std::cout << "Time remaining: " << remainingProcessTime_ << std::endl;
  }
  else {
    std::cout << "Free" << std::endl;
  }
}
