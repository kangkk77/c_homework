# 题目 4：个人任务管理系统

## 学生信息

| 项目 | 内容 |
|------|------|
| 学号 | 202513080172 |
| 姓名 | 待填写 |
| 班级 | 待填写 |
| 作业编号 | 题目 4 |
| 提交日期 | 2026-04-20 |

## 项目简介

本项目使用 C 语言实现了一个命令行版 Todo List，用于管理个人任务。程序支持：

- 添加任务：任务名称、优先级、截止日期、标签
- 状态管理：进行中 / 已完成
- 列表排序：默认按截止日期升序，日期相同时按优先级排序
- 过期提醒：未完成且截止日期早于当前系统日期时显示 `OVERDUE`
- 持久化：任务保存到 `data/tasks.txt`
- 扩展支持：可按标签过滤显示

## 目录结构

```text
c_homework/
|-- README.md
|-- .gitignore
|-- src/
|   |-- main.c
|   |-- task.c
|   |-- task.h
|   |-- storage.c
|   `-- storage.h
`-- data/
    |-- input.txt
    `-- tasks.txt
```

## 功能设计

### 1. 添加任务

命令格式：

```bash
todo add <name> <priority> <YYYY-MM-DD> [tag]
```

示例：

```bash
todo add DraftProposal high 2026-04-24 study
```

说明：

- `priority` 支持 `high`、`medium`、`low`
- `tag` 可选，未填写时默认为 `default`
- 新任务创建后默认状态为 `in-progress`
- 如果任务名包含空格，请使用引号，例如 `todo add "Finish report" high 2026-04-24 study`

### 2. 查看任务

命令格式：

```bash
todo list [tag]
```

示例：

```bash
todo list
todo list study
```

说明：

- 默认显示全部任务
- 传入标签后只显示对应标签任务
- 输出包含任务编号、名称、优先级、截止日期、状态、标签、提醒信息

### 3. 更新任务状态

命令格式：

```bash
todo update <id> <in-progress|completed>
```

示例：

```bash
todo update 1 completed
```

### 4. 排序规则

- 先按截止日期从早到晚排序
- 截止日期相同时，按优先级排序：`high > medium > low`
- 若仍相同，再按任务编号排序

### 5. 过期提醒

若任务满足以下条件，列表中的 Reminder 字段会显示 `OVERDUE`：

- 当前状态不是 `completed`
- 截止日期早于当前系统日期

## 数据持久化格式

任务存储在 `data/tasks.txt` 中，每行一条记录，使用 `|` 分隔：

```text
id|name|priority|due_date|status|tag
```

示例：

```text
1|Finish README|high|2026-04-18|in-progress|study
```

## 编译与运行

在项目根目录执行：

```bash
gcc -Wall -Wextra -pedantic src/main.c src/task.c src/storage.c -o todo
```

运行帮助：

```bash
./todo help
```

添加任务：

```bash
./todo add DraftProposal high 2026-04-24 study
```

查看任务：

```bash
./todo list
```

更新状态：

```bash
./todo update 1 completed
```

## 测试数据说明

`data/tasks.txt` 预置了 3 条任务：

- 一条已过期且未完成的任务，用于测试过期提醒
- 一条已完成任务
- 一条未来任务

`data/input.txt` 给出了建议测试命令，方便手动验证。

## 后续可扩展方向

- 支持中文优先级输入映射
- 支持按周 / 按天周期性任务生成
- 支持删除任务、编辑任务
- 支持更灵活的多词任务名输入

## 提交说明

首次提交建议流程：

```bash
git status
git add .
git commit -m "feat: initialize todo cli project"
git push origin master
```
