#include <sys/inotify.h>
#include <unistd.h>
#include <malloc.h>

#include "FileRemoveDetect.h"
#include "../Macro/Macro.h"




int detectFileRemove(const char* path, struct inotify_event *event)
{
    if(access(path, F_OK) != 0)
    {
        PRINT_LOG("file %s is not exist\n", path);
        return -1;
    }

    int descriptor = inotify_init();
    if(descriptor < 0)
    {
        printf("descriptor\n");
        PRINT_LOG("inotify init failed\n");
        return -1;
    }

    int watchDescriptor = inotify_add_watch(descriptor, path, IN_DELETE_SELF);
    if(watchDescriptor < 0)
    {
        PRINT_LOG("watch failed\n");
        return -1;
    }

    size_t readBytes = read(descriptor, event, sizeof(struct inotify_event));

    inotify_rm_watch(descriptor, IN_DELETE_SELF);

    return 0;
}
