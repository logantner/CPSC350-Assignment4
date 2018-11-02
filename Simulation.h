#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <string>
#include <fstream>
#include "Queue.h"
#include "Office.h"
#include "Student.h"

class Simulation {
public:
  Simulation() { }
  Simulation(std::string fileName) : fileName_(fileName) { }
  ~Simulation() {}
  void run();
  void display() const;
private:
  Office registrarOffice_;
  Queue<Student> line_;
  std::string fileName_;
  int time_ = 0;
  int currentStudentIdx_ = 0;

  void generateOfficeWindows(std::ifstream&);
  void passTime(int);
  // Student methods
  bool studentsToDequeue(int) const;
  void dequeueStudent();
  void processNewStudents(std::ifstream&);
  void addStudentToSimulation(Student);
  void finishProcessingQueue();
  // Output methods
  void reportStatistics(  std::ostream&);
  void reportStudentStats(std::ostream&);
  void reportWindowStats( std::ostream&);
};

#endif
