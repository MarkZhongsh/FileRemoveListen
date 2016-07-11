#include "FileLock.h"
#include "../Macro/Macro.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>


FILE* FileLock::GetFileLock(const char* path, const char* mode, int operation)
{
    if(access(path, F_OK) < 0)
    {
        PRINT_LOG("file %s is not exists\n", path);
        return NULL;
    }

    if(strcmp(mode, "") <= 0)
    {
        PRINT_LOG("mode is empty\n");
        return NULL;
    }

    if( !((operation & LOCK_EX ) || (operation & LOCK_SH)))
    {
        PRINT_LOG("operation is error\n");
        return NULL;
    }

    FILE *lockFile = fopen(path, mode);
    
    if(flock(fileno(lockFile), operation) != 0)
    {
        fclose(lockFile);
        return NULL;
    }

    return lockFile;
}


int FileLock::ReleaseFileLock(FILE *file)
{
    if(file == NULL)
    {
        return 0;
    }

    if(flock(fileno(file), LOCK_UN) != 0)
    {
        return -1;
    }
    return 0;
}
