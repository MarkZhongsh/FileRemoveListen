#ifndef FILELOCK_H_H_
#define FILELOCK_H_H_

#include <sys/file.h>
#include <stdio.h>


class FileLock
{
public:
    static FILE* GetFileLock(const char* path, const char* mode, int operation);
    static int ReleaseFileLock(FILE *file);
private:
    FileLock();
    FileLock(const FileLock&);
    ~FileLock();
};

#endif
