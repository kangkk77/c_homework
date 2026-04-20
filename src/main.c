#include "storage.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORAGE_PATH "data/tasks.txt"

static void print_usage(void) {
    printf("Todo CLI usage:\n");
    printf("  todo add <name> <priority> <YYYY-MM-DD> [tag]\n");
    printf("  todo list [tag]\n");
    printf("  todo update <id> <in-progress|completed>\n");
    printf("  todo help\n");
}

static int add_task(TaskList *list, int argc, char *argv[]) {
    Task task;
    int year = 0;
    int month = 0;
    int day = 0;

    if (argc < 5) {
        fprintf(stderr, "Missing arguments for add.\n");
        return 0;
    }
    if (list->count >= MAX_TASKS) {
        fprintf(stderr, "Task storage is full.\n");
        return 0;
    }
    if (strlen(argv[2]) >= MAX_NAME_LEN) {
        fprintf(stderr, "Task name is too long.\n");
        return 0;
    }
    if (!parse_priority(argv[3], &task.priority)) {
        fprintf(stderr, "Priority must be high, medium, or low.\n");
        return 0;
    }
    if (!parse_date(argv[4], &year, &month, &day)) {
        fprintf(stderr, "Date must use YYYY-MM-DD format.\n");
        return 0;
    }

    task.id = list->next_id++;
    strcpy(task.name, argv[2]);
    strcpy(task.due_date, argv[4]);
    task.status = STATUS_IN_PROGRESS;

    if (argc >= 6) {
        if (strlen(argv[5]) >= MAX_TAG_LEN) {
            fprintf(stderr, "Tag is too long.\n");
            return 0;
        }
        strcpy(task.tag, argv[5]);
    } else {
        strcpy(task.tag, "default");
    }

    list->items[list->count++] = task;
    sort_tasks(list);
    printf("Added task #%d.\n", task.id);
    return 1;
}

static void print_task_header(void) {
    printf("%-4s %-24s %-8s %-12s %-12s %-10s %s\n", "ID", "Name", "Priority", "Due Date", "Status", "Tag", "Reminder");
}

static void print_task(const Task *task) {
    printf(
        "%-4d %-24s %-8s %-12s %-12s %-10s %s\n",
        task->id,
        task->name,
        priority_to_string(task->priority),
        task->due_date,
        status_to_string(task->status),
        task->tag,
        is_overdue(task) ? "OVERDUE" : "-"
    );
}

static int list_tasks(TaskList *list, int argc, char *argv[]) {
    const char *filter_tag = NULL;
    int index = 0;
    int matched = 0;

    if (argc >= 3) {
        filter_tag = argv[2];
    }

    sort_tasks(list);
    print_task_header();
    for (index = 0; index < list->count; ++index) {
        const Task *task = &list->items[index];
        if (filter_tag != NULL && strcmp(task->tag, filter_tag) != 0) {
            continue;
        }
        print_task(task);
        matched = 1;
    }

    if (!matched) {
        printf("No tasks found.\n");
    }
    return 1;
}

static int update_task(TaskList *list, int argc, char *argv[]) {
    int id = 0;
    TaskStatus status;
    Task *task = NULL;

    if (argc < 4) {
        fprintf(stderr, "Missing arguments for update.\n");
        return 0;
    }

    id = atoi(argv[2]);
    if (id <= 0) {
        fprintf(stderr, "Task id must be a positive integer.\n");
        return 0;
    }
    if (!parse_status(argv[3], &status)) {
        fprintf(stderr, "Status must be in-progress or completed.\n");
        return 0;
    }

    task = find_task_by_id(list, id);
    if (task == NULL) {
        fprintf(stderr, "Task #%d not found.\n", id);
        return 0;
    }

    task->status = status;
    sort_tasks(list);
    printf("Updated task #%d to %s.\n", id, status_to_string(status));
    return 1;
}

int main(int argc, char *argv[]) {
    TaskList list;
    int success = 1;

    if (!load_tasks(STORAGE_PATH, &list)) {
        fprintf(stderr, "Failed to load tasks from %s.\n", STORAGE_PATH);
        return 1;
    }

    if (argc < 2 || strcmp(argv[1], "help") == 0) {
        print_usage();
        return 0;
    }

    if (strcmp(argv[1], "add") == 0) {
        success = add_task(&list, argc, argv);
    } else if (strcmp(argv[1], "list") == 0) {
        success = list_tasks(&list, argc, argv);
    } else if (strcmp(argv[1], "update") == 0) {
        success = update_task(&list, argc, argv);
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        print_usage();
        return 1;
    }

    if (!success) {
        return 1;
    }
    if ((strcmp(argv[1], "add") == 0 || strcmp(argv[1], "update") == 0) && !save_tasks(STORAGE_PATH, &list)) {
        fprintf(stderr, "Failed to save tasks.\n");
        return 1;
    }

    return 0;
}
