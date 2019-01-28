#include "streamwriter.h"
#ifdef _WIN32
#include <io.h>
#include <Windows.h>
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif

using namespace jsonrpc;
using namespace std;

bool StreamWriter::Write(const string &source, int fd) {
  ssize_t bytesWritten;
  size_t totalSize = source.size();
  size_t remainingSize = totalSize;

  do {
    bytesWritten =
        write(fd, source.c_str() + (totalSize - remainingSize), remainingSize);
    if (bytesWritten < 0) {
      return false;
    } else {
      remainingSize -= static_cast<size_t>(bytesWritten);
    }
  } while (remainingSize > 0);
  return true;
}
