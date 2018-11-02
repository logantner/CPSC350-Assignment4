#include <iostream>   // For cout, endl,
#include <string>
#include <fstream>
#include "Simulation.h"
#include "Stats.h"

using std::cout;
using std::endl;
using std::ifstream;

void Simulation::run() {
  // Open file, verify that it exists
  ifstream fin (fileName_);
  if ( !fin.is_open() ) {
    cout << "The file " << fileName_ << " could not be found." << endl;
    return;
  }

  generateOfficeWindows(fin);

  int nextTime;
  // While new students continue to arrive:
  while (fin >> nextTime) {
    fin.ignore();
    // Handle students currently in the queue that will be paired with a window
    // prior to the arrival of new students
    while ( studentsToDequeue(nextTime - time_) ) {
      passTime( registrarOffice_.minWindowTime() );
      dequeueStudent();
    }
    // Handle the next batch of arriving students (to queue or windows)
    passTime(nextTime - time_);
    processNewStudents(fin);
  }
  // finish processing students still in the simulation
  finishProcessingQueue();
  passTime( registrarOffice_.maxWindowTime() );

  reportStatistics(cout);
}

void Simulation::generateOfficeWindows(ifstream& fin) {
  // Reads in the number of office windows and adds them to the registrar office
  int numWindows;
  fin >> numWindows;
  fin.ignore();

  registrarOffice_ = Office(numWindows);
}

bool Simulation::studentsToDequeue(int timeUntilNextArrival) const {
  // Returns true if students remain in the queue and at least one window will
  // free up before the time of the next student arrival
  if ( line_.isEmpty() ) {
    return false;
  }
  return ( registrarOffice_.minWindowTime() <= timeUntilNextArrival );
}

void Simulation::passTime(int timeToPass) {
  // Updates the simulation time and recorded times of each office window
  time_ += timeToPass;
  registrarOffice_.passTime(timeToPass);
}

void Simulation::dequeueStudent() {
  // Moves a student from the line to an available window
  // Updates the amount of time waited to the repository
  Student student = line_.remove();
  registrarOffice_.pairStudentWithWindow(student, time_);
}

void Simulation::processNewStudents(ifstream& fin) {
  // Reads in students from the file and inserts them into either a free
  // window, or the queue if no window is available.
  int numStudents;
  fin >> numStudents; fin.ignore();

  int windowTime;
  for (int i=0; i<numStudents; ++i) {
    fin >> windowTime; fin.ignore();
    Student s = {currentStudentIdx_++, time_, windowTime};
    addStudentToSimulation(s);
  }
}

void Simulation::addStudentToSimulation(Student student) {
  // Tries pairing the student with a free registrar indow first, then inserts
  // them into a queue if none are available
  if ( registrarOffice_.availableWindow() ) {
    registrarOffice_.pairStudentWithWindow(student, time_);
  }
  else {
    line_.insert(student);
  }
}

void Simulation::finishProcessingQueue() {
  // Continues assigning students to the next available window until no students
  // remain in the queue
  while ( !line_.isEmpty() ) {
    passTime( registrarOffice_.minWindowTime() );
    dequeueStudent();
  }
}

void Simulation::reportStatistics(std::ostream& out) {
  reportStudentStats(out);
  reportWindowStats(out);
}

void Simulation::reportStudentStats(std::ostream& out) {
  // Extracts the student wait times as an array
  int numStudents = registrarOffice_.waitingTimes().getSize();
  int studentTimes[ numStudents ];
  for (int i=0; i<numStudents; ++i) {
    studentTimes[i] = registrarOffice_.waitingTimes().removeFront();
  }

  // Outputs statistics
  out << "Mean student wait time:    " << mean(studentTimes, numStudents)   << endl;
  out << "Median student wait time:  " << median(studentTimes, numStudents) << endl;
  out << "Maximum student wait time: " << max(studentTimes, numStudents)    << endl;
  out << "Number of students waiting more than 10 minutes: "
      << numOver(studentTimes, numStudents, 10) << endl;
}

void Simulation::reportWindowStats(std::ostream& out) {
  // Extracts window idle times as an array
  int numWindows = registrarOffice_.numWindows();
  int windowTimes[ numWindows ];
  for (int i=0; i<numWindows; ++i) {
    windowTimes[i] = registrarOffice_.idleTime(i);
  }

  // Outputs statistics
  out << "Mean idle window time: " << mean(windowTimes, numWindows) << endl;
  out << "Max idle window time:  " << max( windowTimes, numWindows) << endl;
  out << "Number of windows idle more than 5 minutes: "
      << numOver(windowTimes, numWindows, 5) << endl;
}

void Simulation::display() const {
  cout << "Time: " << time_ << endl;
  cout << "The line has " << line_.size() << " students." << endl;
  registrarOffice_.display();
}
