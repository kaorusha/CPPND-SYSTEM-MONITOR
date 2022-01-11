#include <string>
#include <chrono>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
// https://stackoverflow.com/questions/60046147/how-to-convert-chronoseconds-to-string-in-hhmmss-format-in-c
string Format::ElapsedTime(long seconds) {
  using namespace std::chrono;
  string result;
  if (seconds < 0) {
      seconds  *= -1;
      result.push_back('-');
  }
  std::chrono::seconds secs(seconds);
  auto h = duration_cast<hours>(secs);
  secs -= h;
  auto m = duration_cast<minutes>(secs);
  secs -= m;
  if (h < 10h) result.push_back('0');
  result += std::to_string(h.count());
  result += ':';
  if (m< 10min) result.push_back('0');
  result += std::to_string(m.count());
  result += ':';
  if (secs < 10s) result.push_back('0');
  result += std::to_string(secs.count());

  return result;
}