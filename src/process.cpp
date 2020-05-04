#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include <iostream>
using std::string;
using std::to_string;
using std::vector;

Process::Process(int pidP): pid(pidP){
    // calculate cpu util
    this->cpuUtil = LinuxParser::CpuUtilization(pid);
    // command
    this->command = LinuxParser::Command(pid);
    // RAM
    this->ram = LinuxParser::Ram(this->pid);
    // User
    this->user = LinuxParser::User(this->pid);
    // uptime
    this->uptime = LinuxParser::UpTime(this->pid);
}

// TODO: Return this process's ID
int Process::Pid() { return this->pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return this->cpuUtil; }

// TODO: Return the command that generated this process
string Process::Command() { return this->command; }

// TODO: Return this process's memory utilization
string Process::Ram() { return this->ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return this->user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return this->uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return this->cpuUtil > a.cpuUtil; }