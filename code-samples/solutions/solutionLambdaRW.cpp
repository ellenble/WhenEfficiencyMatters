#include <cstdint>
#include <cstdio>

#ifndef _MSC_VER
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#else
#ifndef SEEK_SET
#define SEEK_SET 1
#endif
#define O_RDWR 1

int lseek(int, int, int)
{
  return 0;
}

void close(int) {}

int open(const char*, int, int)
{
  return 3;
}

int read(int, char*, size_t)
{
  return -1;
}
int write(int, const char*, size_t)
{
  return -1;
}
#endif

void Close(int& fd)
{
  if(-1 != fd) {
    close(fd);
    fd = -1;
  }
}
//---------------------------------------------------------------------------

class AutoFreeFD {
public:
  AutoFreeFD(int fd)
  : mFD{fd}
  {}

  AutoFreeFD& operator=(const int& fd)
  {
    mFD = fd;
    return *this;
  }

  ~AutoFreeFD() { Close(mFD); }

  operator int() const { return mFD; }

private:
  int mFD;
};
//---------------------------------------------------------------------------

struct FileHeader {
  uint32_t checksum;
};
//---------------------------------------------------------------------------

bool SkipBytesFromBeginning(int fd, size_t len)
{
  return len == lseek(fd, len, SEEK_SET);
}
//---------------------------------------------------------------------------

template<typename ACTION>
bool ReadWriteExact(int fd, size_t dataLen, ACTION&& action)
{
  const auto ret = action(fd, dataLen);

  if(-1 == ret) { return false; }

  return dataLen == static_cast<size_t>(ret);
}
//---------------------------------------------------------------------------

bool ReadExact(int fd, char* data, size_t dataLen)
{
  return ReadWriteExact(fd, dataLen, [&](int f, size_t l) { return read(f, data, l); });
}
//---------------------------------------------------------------------------

bool WriteExact(int fd, const char* data, size_t dataLen)
{
  return ReadWriteExact(fd, dataLen, [&](int f, size_t l) { return write(f, data, l); });
}
//---------------------------------------------------------------------------

template<typename ACTION>
bool ReadWriteBlock(const int fileId, ACTION&& action)
{
  char fileName[1'024];
  snprintf(fileName, sizeof(fileName), "file-%d.bin", fileId);

  AutoFreeFD fd = open(fileName, O_RDWR, 0);

  if(-1 == fd) {
    printf("file open failed %s\n", fileName);
    return false;
  }

  if(!SkipBytesFromBeginning(fd, sizeof(FileHeader))) { return false; }

  if(action(fd)) { return true; }

  return false;
}
//---------------------------------------------------------------------------

bool ReadBlock(char* data, size_t dataLen, const int fileId)
{
  return ReadWriteBlock(fileId, [&](int ffd) { return ReadExact(ffd, data, dataLen); });
}
//---------------------------------------------------------------------------

bool WriteBlock(const char* data, size_t dataLen, const int fileId)
{
  return ReadWriteBlock(fileId, [&](int ffd) { return WriteExact(ffd, data, dataLen); });
}
//---------------------------------------------------------------------------

int main()
{
  WriteBlock("hello", 4, 2);
  char buffer[5];
  ReadBlock(buffer, 4, 2);
}
