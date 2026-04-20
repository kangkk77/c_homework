#ifndef TASK_H
#define TASK_H

#define MAX_TASKS 256
#define MAX_NAME_LEN 128
#define MAX_DATE_LEN 11
#define MAX_TAG_LEN 32

typedef enum {
    PRIORITY_HIGH = 0,
    PRIORITY_MEDIUM = 1,
    PRIORITY_LOW = 2
} Priority;

typedef enum {
    STATUS_IN_PROGRESS = 0,
    STATUS_COMPLETED = 1
} TaskStatus;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    Priority priority;
    char due_date[MAX_DATE_LEN];
    TaskStatus status;
    char tag[MAX_TAG_LEN];
} Task;

typedef struct {
    Task items[MAX_TASKS];
    int count;
    int next_id;
} TaskList;

int parse_priority(const char *text, Priority *priority);
const char *priority_to_string(Priority priority);
int parse_status(const char *text, TaskStatus *status);
const char *status_to_string(TaskStatus status);
int parse_date(const char *text, int *year, int *month, int *day);
int compare_tasks(const void *left, const void *right);
int is_overdue(const Task *task);
void sort_tasks(TaskList *list);
Task *find_task_by_id(TaskList *list, int id);

#endif
