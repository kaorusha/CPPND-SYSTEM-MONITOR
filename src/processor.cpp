#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  if (nonIdle==0) {
    nonIdle = LinuxParser::ActiveJiffies();
  } else {
    prevNonIdle = nonIdle;
    nonIdle = LinuxParser::ActiveJiffies();
  }
  if (idle==0) {
    idle = LinuxParser::IdleJiffies();
  } else {
    prevIdle = idle;
    idle = LinuxParser::IdleJiffies();
  }
  // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux  
  long prevTotal = prevIdle + prevNonIdle;
  long total = idle + nonIdle;

  float totald = total - prevTotal;
  float idled = idle - prevIdle;

  return (totald - idled)/totald;
}