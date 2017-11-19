#include "Utility.hh"

#include <sstream>

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    if (!item.empty()) elems.push_back(std::move(item));
  }
  return elems;
}

