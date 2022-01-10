#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

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
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
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
  string line;
  string key;
  int value;
  float total, free;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") total = value;
      if (key == "MemFree:") {
        free = value;
        return (total - free)/total;
      }
    }
  }
  return 0.0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  long sec;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> sec;
  }
  return sec;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  vector<string> jeffies = CpuUtilization();
  return stoi(jeffies[kUser_]) +\
         stoi(jeffies[kNice_]) +\
         stoi(jeffies[kSystem_]) +\
         stoi(jeffies[kIdle_]) +\
         stoi(jeffies[kIOwait_]) +\
         stoi(jeffies[kIRQ_]) +\
         stoi(jeffies[kSoftIRQ_]) +\
         stoi(jeffies[kSteal_]) +\
         stoi(jeffies[kGuest_]) +\
         stoi(jeffies[kGuestNice_]);
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  string line;
  string value;
  vector<string> jiffies;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if(stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      jiffies.push_back(value);
    }
  } 
  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  return stoi(jiffies[13]) +\
         stoi(jiffies[14]) +\
         stoi(jiffies[15]) +\
         stoi(jiffies[16]);
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  vector<string> jeffies = CpuUtilization();
  return stoi(jeffies[kUser_]) +\
         stoi(jeffies[kNice_]) +\
         stoi(jeffies[kSystem_]) +\
         stoi(jeffies[kIRQ_]) +\
         stoi(jeffies[kSoftIRQ_]) +\
         stoi(jeffies[kSteal_]);
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  vector<string> jeffies = CpuUtilization();
  return stoi(jeffies[kIdle_]) +\
         stoi(jeffies[kIOwait_]);
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string value;
  vector<string> output;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    // get the first line
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> value) {
      if (value == "cpu")
        continue;
      else
        output.push_back(value);
    }
  }
  return output;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") return value;
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") return value;
    }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  std::getline(stream, line);
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line;
  string key;
  string value;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      // capture the first integer 
      linestream >> key >> value;
      if (key == "VmSize:") return value;
    }
  }
  return string();
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line;
  string key;
  string value;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      // capture the first integer 
      linestream >> key >> value;
      if (key == "Uid:") return value;
    }
  }
  return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::ifstream stream(kPasswordPath);
  string line;
  string user;
  string x;
  string id;
  string uid = Uid(pid);
  if (stream.is_open()){
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> x >> id;
      if (id == uid) return user;
    }
  }
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  string value;
  int index = 0;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if(stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      ++index;
      // starttime
      if (index == 22)
        return stol(value);
    }
  } 
  return 0;
}
