#ifndef STORAGE_H
#define STORAGE_H

#include "task.h"

int load_tasks(const char *path, TaskList *list);
int save_tasks(const char *path, const TaskList *list);

#endif
