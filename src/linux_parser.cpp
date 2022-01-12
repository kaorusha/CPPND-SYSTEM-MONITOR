#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
#define print(x) std::cout<< "Variable: " << (#x) << " = " << x << "\n"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

template <typename T>
T findValueByKey(string const &keyFilter, string const &filename) {
  string line;
  string key;
  T value;

  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == keyFilter) {
          filestream.close();
          return value;
        } 
      }
    }
  }
  filestream.close();
  return value;
};

template <typename T>
T getValueOfFile(string const &filename) {
  string line;
  T value;

  std::ifstream filestream(filename);
  if (filestream.is_open()) {
    std::getline(filestream,line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  filestream.close();
  return value;
};

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
        if (key == filterOS) {
          std::replace(value.begin(), value.end(), '_', ' ');
          filestream.close();
          return value;
        }
      }
    }
  }
  filestream.close();
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
  stream.close();
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
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string filename = kProcDirectory + kMeminfoFilename;
  float total = findValueByKey<float>( filterMemTotalString, filename);
  float free = findValueByKey<float>( filterMemFreeString, filename);
  return (total - free)/total;
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  return getValueOfFile<long>( kProcDirectory + kUptimeFilename);
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
      jiffies.emplace_back(value);
    }
  } 
  stream.close();
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
      if (value == filterCpu)
        continue;
      else
        output.emplace_back(value);
    }
  }
  stream.close();
  return output;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  return findValueByKey<int>(filterProcesses, kProcDirectory + kStatFilename);
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  return findValueByKey<int>(filterRunningProcesses, kProcDirectory + kStatFilename); 
}

// Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  return getValueOfFile<string>(kProcDirectory + to_string(pid) + kCmdlineFilename);
}

// Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  // replace VmSize with VmRSS
  // VmSize: virtual memory size
  // VmRSS: exact physical memory being used
  return findValueByKey<string>( filterProcMem, kProcDirectory + to_string(pid) + kStatusFilename);
}

// Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  return findValueByKey<string>( filterUID, kProcDirectory + to_string(pid) + kStatusFilename);
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
  stream.close();
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
  stream.close(); 
  return 0;
}
