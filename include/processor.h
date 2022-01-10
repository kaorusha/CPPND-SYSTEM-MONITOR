#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  Processor():prevIdle(0), idle(0), prevNonIdle(0), nonIdle(0) {}
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  long prevIdle;
  long idle;
  long prevNonIdle;
  long nonIdle;
};

#endif