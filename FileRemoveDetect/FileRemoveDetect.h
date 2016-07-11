#ifndef FILEREMOVEDETECT_H_H_
#define FILEREMOVEDETECT_H_H_

#include <stdio.h>
#include <sys/inotify.h>


int detectFileRemove(const char* detectPath, struct inotify_event *event);

#endif
