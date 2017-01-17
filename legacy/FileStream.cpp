#include "ErrLog.h"
#include "FileStream.h"

FileStream::FileStream()
{
  Reset();
}

FileStream::~FileStream()
{
  Reset();
}

void FileStream::Reset()
{
  Initialised = false;
  TheStream = 0;
}
  
bool FileStream::OpenStream(const std::string& filename, bool append)
{
  std::cout << "FileStream::OpenStream called." << std::endl;
  if(!Initialised)
  {
    TheStream = new std::ofstream(filename, (append ? std::ios_base::app : std::ios_base::out));
    if(TheStream == 0)
    {
      ErrLog("Failed to allocate TheStream");
    }
    if(TheStream->fail())
    {
      ErrLog("Failure to open TheStream.");
    }
    
    Initialised = true;
  }
  else
  {
    ErrLog("Already initialised!");
  }
  
  return Initialised;
}

bool FileStream::Close()
{
  std::cout << "FileStream::Close called." << std::endl;
  if(!Initialised)
  {
    delete TheStream;
  }
  
  Reset();
  return Initialised;
}
  
void FileStream::Write(const std::string& line)
{
  if(!Initialised)
    return;
  
  (*TheStream) << line << std::endl;
  std::cout << "Written [" << line << "] to file." << std::endl;
}
