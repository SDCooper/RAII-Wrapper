#ifndef ERRLOG_H
#define ERRLOG_H

#include <iostream>
#include <string>

// Log line to stderr and flush the stream.
inline void ErrLog(const std::string& line)
{
  std::cerr << line << std::endl;
}

#endif // ERRLOG_H
