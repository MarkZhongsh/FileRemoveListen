#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/inotify.h>
#include <errno.h>
#include <malloc.h>
#include <unistd.h>

#include "FileLock/FileLock.h"
#include "FileRemoveDetect/FileRemoveDetect.h"

int main()
{
    const char *path = "./log.txt";
    FILE *lockFile = FileLock::GetFileLock(path, "w+", LOCK_EX);
    if(lockFile)
    {
        printf("create lockFile success!\n");
    }
    else
    {
        printf("create lockFile failed!\n");
        return -1;
    }

    const char *detectFile = "test";
    struct inotify_event event;
    int removeRet = detectFileRemove(detectFile, &event);
    printf("removeRet :%d\n", removeRet);
    if(removeRet == 0)
    {
        printf("file \"%s\" is removed\n",detectFile);
        fprintf(lockFile, "file is removed\n");
    }
    else
    {
        printf("detect error\n");
    }



    int ret = FileLock::ReleaseFileLock(lockFile);
    if(ret == 0)
    {
        printf("ReleaseFileLock success\n");
    }
    else
    {
        fclose(lockFile);
        return -1;
    }
    fclose(lockFile);
    return 0;
}

//int main()
//{
//    const char* watchFilePath = "/home/mark/c++/FileRemoveListen/test";
//
//    if(access(watchFilePath, F_OK) < 0)
//    {
//        printf("no such file\n");
//        return -1;
//    }
//    int notifyId = inotify_init();
//
//    printf("notifyId: %d\n",notifyId);
//    if(notifyId < 0)
//    {
//        assert("cant not init");
//        return -1;
//    }
//
//    printf("begin watch\n");
//    int watchId = inotify_add_watch(notifyId, watchFilePath, IN_DELETE);
//
//    if(watchId < 0)
//    {
//        assert("cant not add watch");
//        return -1;
//    }
//
//    void *p_buf = malloc(sizeof(struct inotify_event));
//
//    size_t readBytes = read(notifyId, p_buf, sizeof(struct inotify_event));
//
//    printf("file is removed\n");
//
//    inotify_rm_watch(notifyId, IN_DELETE_SELF);
//
//    free(p_buf);
//
//    return 0;
//}
