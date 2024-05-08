#ifndef PGS_POCEX_CONSTANTS
#define PGS_POCEX_CONSTANTS

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

inline constexpr uint32_t PORT = 5555;
inline const std::string ADDR  = "127.0.0.1";

std::string bufferToHexStr(const char *buffer, size_t const size) {
  std::stringstream s;
  s << std::setfill('0');
  for (size_t i = 0; i < size; ++i) {
    s << std::hex << std::setw(2) << (unsigned)(unsigned char)buffer[i];
    s << (((i + 1) % 16 == 0) ? "\n" : " ");
  }
  return s.str();
}

#endif