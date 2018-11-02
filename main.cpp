#include <iostream>
#include <string>
#include "Simulation.h"

int main(int argc, char** argv) {
  if (argc <= 1) {
    std::cout << "You are required to provide a file name for this program"
              << std::endl;
    return 1;
  }

  std::string fileName (argv[1]);
  Simulation sim (fileName);
  sim.run();

  return 0;
}
