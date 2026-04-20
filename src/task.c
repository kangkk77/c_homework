#include "task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int compare_priority(Priority left, Priority right) {
    return (int)left - (int)right;
}

int parse_priority(const char *text, Priority *priority) {
    if (strcmp(text, "high") == 0 || strcmp(text, "H") == 0) {
        *priority = PRIORITY_HIGH;
        return 1;
    }
    if (strcmp(text, "medium") == 0 || strcmp(text, "M") == 0) {
        *priority = PRIORITY_MEDIUM;
        return 1;
    }
    if (strcmp(text, "low") == 0 || strcmp(text, "L") == 0) {
        *priority = PRIORITY_LOW;
        return 1;
    }
    return 0;
}

const char *priority_to_string(Priority priority) {
    switch (priority) {
        case PRIORITY_HIGH:
            return "high";
        case PRIORITY_MEDIUM:
            return "medium";
        case PRIORITY_LOW:
            return "low";
        default:
            return "unknown";
    }
}

int parse_status(const char *text, TaskStatus *status) {
    if (strcmp(text, "in-progress") == 0) {
        *status = STATUS_IN_PROGRESS;
        return 1;
    }
    if (strcmp(text, "completed") == 0) {
        *status = STATUS_COMPLETED;
        return 1;
    }
    return 0;
}

const char *status_to_string(TaskStatus status) {
    switch (status) {
        case STATUS_IN_PROGRESS:
            return "in-progress";
        case STATUS_COMPLETED:
            return "completed";
        default:
            return "unknown";
    }
}

int parse_date(const char *text, int *year, int *month, int *day) {
    if (sscanf(text, "%d-%d-%d", year, month, day) != 3) {
        return 0;
    }
    if (*month < 1 || *month > 12 || *day < 1 || *day > 31) {
        return 0;
    }
    return 1;
}

static int compare_date_strings(const char *left, const char *right) {
    int left_year = 0;
    int left_month = 0;
    int left_day = 0;
    int right_year = 0;
    int right_month = 0;
    int right_day = 0;

    if (!parse_date(left, &left_year, &left_month, &left_day)) {
        return 1;
    }
    if (!parse_date(right, &right_year, &right_month, &right_day)) {
        return -1;
    }

    if (left_year != right_year) {
        return left_year - right_year;
    }
    if (left_month != right_month) {
        return left_month - right_month;
    }
    return left_day - right_day;
}

int compare_tasks(const void *left, const void *right) {
    const Task *task_left = (const Task *)left;
    const Task *task_right = (const Task *)right;
    int date_comparison = compare_date_strings(task_left->due_date, task_right->due_date);
    if (date_comparison != 0) {
        return date_comparison;
    }

    if (task_left->status != task_right->status) {
        return (int)task_left->status - (int)task_right->status;
    }

    if (task_left->priority != task_right->priority) {
        return compare_priority(task_left->priority, task_right->priority);
    }

    return task_left->id - task_right->id;
}

int is_overdue(const Task *task) {
    int year = 0;
    int month = 0;
    int day = 0;
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    if (task->status == STATUS_COMPLETED) {
        return 0;
    }
    if (today == NULL || !parse_date(task->due_date, &year, &month, &day)) {
        return 0;
    }

    if (year != today->tm_year + 1900) {
        return year < today->tm_year + 1900;
    }
    if (month != today->tm_mon + 1) {
        return month < today->tm_mon + 1;
    }
    return day < today->tm_mday;
}

void sort_tasks(TaskList *list) {
    qsort(list->items, (size_t)list->count, sizeof(Task), compare_tasks);
}

Task *find_task_by_id(TaskList *list, int id) {
    int index = 0;
    for (index = 0; index < list->count; ++index) {
        if (list->items[index].id == id) {
            return &list->items[index];
        }
    }
    return NULL;
}
