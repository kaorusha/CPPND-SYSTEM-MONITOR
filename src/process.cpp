#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;
#define MAX_CMD_LEN 50

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{

  float active_sec = LinuxParser::ActiveJiffies(Pid()) / sysconf(_SC_CLK_TCK);
  return active_sec / (float)UpTime();
}

// TODO: Return the command that generated this process
string Process::Command() {
  string command(LinuxParser::Command(Pid()));
  if (command.length() > MAX_CMD_LEN) {
    command.resize(MAX_CMD_LEN);
    command += "...";
  }
  return command;
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  string kb = LinuxParser::Ram(Pid());
  // some process has no VmSize so returned empty string
  if (kb == "")
    return "0";
  std::istringstream linestream(kb);
  int mb;
  linestream >> mb;
  mb *= 0.001;
  return to_string(mb);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const{
  // uptime of the system minus process start time
  return LinuxParser::UpTime() - LinuxParser::UpTime(Pid()) / sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization(); }