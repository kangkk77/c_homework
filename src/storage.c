#include "storage.h"

#include <stdio.h>
#include <string.h>

int load_tasks(const char *path, TaskList *list) {
    FILE *file = fopen(path, "r");
    char line[512];

    list->count = 0;
    list->next_id = 1;

    if (file == NULL) {
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        Task task;
        char priority_buffer[16];
        char status_buffer[16];
        char *newline = strchr(line, '\n');
        int scanned = 0;

        if (newline != NULL) {
            *newline = '\0';
        }
        if (line[0] == '\0') {
            continue;
        }

        scanned = sscanf(
            line,
            "%d|%127[^|]|%15[^|]|%10[^|]|%15[^|]|%31[^|]",
            &task.id,
            task.name,
            priority_buffer,
            task.due_date,
            status_buffer,
            task.tag
        );

        if (scanned < 5 || list->count >= MAX_TASKS) {
            continue;
        }
        if (scanned == 5) {
            strcpy(task.tag, "default");
        }
        if (!parse_priority(priority_buffer, &task.priority)) {
            continue;
        }
        if (!parse_status(status_buffer, &task.status)) {
            continue;
        }

        list->items[list->count++] = task;
        if (task.id >= list->next_id) {
            list->next_id = task.id + 1;
        }
    }

    fclose(file);
    return 1;
}

int save_tasks(const char *path, const TaskList *list) {
    FILE *file = fopen(path, "w");
    int index = 0;

    if (file == NULL) {
        return 0;
    }

    for (index = 0; index < list->count; ++index) {
        const Task *task = &list->items[index];
        fprintf(
            file,
            "%d|%s|%s|%s|%s|%s\n",
            task->id,
            task->name,
            priority_to_string(task->priority),
            task->due_date,
            status_to_string(task->status),
            task->tag
        );
    }

    fclose(file);
    return 1;
}
