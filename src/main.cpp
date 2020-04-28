#include <iostream>

#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

int main() {
  // System system;
  // NCursesDisplay::Display(system);
  std::cout << "\n\n\n**** LINUX_PARSER_TEST ****" << std::endl;
  std::cout << "Memory Utilization: " << LinuxParser::MemoryUtilization() << std::endl;
  std::cout << "Uptime: " << LinuxParser::UpTime() << std::endl;
}