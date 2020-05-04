#include <iostream>

#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include <unistd.h>
int main() {
  System system;
  NCursesDisplay::Display(system);
  // // used for testing
  // std::cout << "\n\n\n**** LINUX_PARSER_TEST ****" << std::endl;
  // std::cout << "Memory Utilization: " << LinuxParser::MemoryUtilization() << std::endl;
  // std::cout << "Uptime: " << LinuxParser::UpTime() << std::endl;
  // std::cout << "System Total Jiffies: " << LinuxParser::Jiffies() << std::endl;
  // std::cout << "System Active Jiffies: " << LinuxParser::ActiveJiffies() << std::endl;
  // std::cout << "System Idle Jiffies: " << LinuxParser::IdleJiffies() << std::endl;
  // std::cout << "Active Jiffies 1: " << LinuxParser::ActiveJiffies(1) << std::endl;
  // std::cout << "Total Processes: " << LinuxParser::TotalProcesses() << std::endl;
  // std::cout << "Running Processes: " << LinuxParser::RunningProcesses() << std::endl;
  // std::cout << "Command for proc: " << LinuxParser::Command(1) << std::endl;
  // std::cout << "Ram for proc: " << LinuxParser::Ram(1) << std::endl;
  // std::cout << "UID for proc: " << LinuxParser::Uid(1) << std::endl;
  // std::cout << "CPU util: " << system.Cpu() << std::endl;
  // usleep(2000000);
  // std::cout << "CPU util: " << system.Cpu() << std::endl;
  // usleep(2000000);
  // std::cout << "CPU util: " << system.Cpu() << std::endl;
}