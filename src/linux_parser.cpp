#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#include "processor.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  // used to parse the file
  string line, key, value;
  // to calculate utilizaiton we take available / total
  float memTotal=0.0, memAvailable=0.0;
  // open the file in /proc/memInfo
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    // get every line in the file
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      // if we find memtotal then save the float value
      if (key.find("MemTotal") != std::string::npos){
        memTotal = stof(value);
      }
      // if we find memavailable then save the float value
      else if (key.find("MemAvailable") != std::string::npos){
        memAvailable = stof(value);
      }
    }
  }
  return 1 - ((memAvailable / memTotal) * 1); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
    // used to parse the file
  string line;
  // to calculate utilizaiton we take available / total
  long uptime=0, idleProcess=0;
  // open the file in /proc/memInfo
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idleProcess;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  // help from https://knowledge.udacity.com/questions/129844
  return LinuxParser::UpTime() * sysconf(_SC_CLK_TCK);
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  // help from https://knowledge.udacity.com/questions/129844
  // used to parse the file
  string line, key;
  // to calculate total jiffies
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get the first line in the file
    std::getline(stream, line);
    std::istringstream linestream(line);
    // read in all the values
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    // sum up all the values
    return user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
  }
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  // help from https://knowledge.udacity.com/questions/129844
  // used to parse the file
  string line, key;
  // to calculate total jiffies
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get the first line in the file
    std::getline(stream, line);
    std::istringstream linestream(line);
    // read in all the values
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    // sum up all the values
    return idle + iowait;
  }
  return 0; 
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  // used to parse the file
  string line, key, value;
  // open the file in /proc/memInfo
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get every line in the file
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      // if we find memtotal then save the float value
      if (key.find("processes") != std::string::npos){
        return stoi(value);
      }
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  // used to parse the file
  string line, key, value;
  // open the file in /proc/memInfo
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get every line in the file
    while(std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      // if we find memtotal then save the float value
      if (key.find("procs_running") != std::string::npos){
        return stoi(value);
      }
    }
  }
  return 0;   
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  // help from https://knowledge.udacity.com/questions/129844
  // used to parse the file pulling one token off at a time
  string line, token;
  // used to sum the total jiffies
  long total(0);
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    // get the first line in the file
    std::getline(stream, line);
    std::istringstream linestream(line);
    // skip the first 13 tokens
    for (int i=0; i<13; i++){
      linestream >> token;
    }
    // sum the next 3 tokens
    for (int i=0; i<4; i++){
      linestream >> token;
      total += std::stol(token);;
    }
  }
  return total; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line, command;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    // get the first line in the file
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;
  }
  return command; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  // used to parse the file pulling one token off at a time
  string line, key, value;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    // get the first line in the file
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key.find("VmSize:") != std::string::npos){
        // return RAM in kilobytes
        return value;
      }
    }
  }
  return "N/A";   
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  // used to parse the file pulling one token off at a time
  string line, key, value;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    // get the first line in the file
    while(std::getline(stream, line)){
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key.find("Uid:") != std::string::npos){
        return value;
      }
    }
  }
  return "N/A"; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return CPU utilization
Processor LinuxParser::CpuUtilization() { 
  // help from https://knowledge.udacity.com/questions/129844
  // used to parse the file
  string line, key;
  // to calculate total jiffies
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  // open the file in /proc/stat
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get the first line in the file
    std::getline(stream, line);
    std::istringstream linestream(line);
    // read in all the values
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    // sum up all the values
    return Processor(user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice);
  }
  return Processor(); 
}