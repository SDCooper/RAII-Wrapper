#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <fstream>

class FileStream
{
public:
  FileStream();
  virtual ~FileStream();
  
  bool OpenStream(const std::string& filename, bool append);
  bool Close();
  
  void Write(const std::string& line);
  
private:
  bool Initialised;
  
  std::ofstream *TheStream;
  
  void Reset();
  
};

#endif // FILESTREAM_H
