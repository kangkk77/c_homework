# C/C++ 程序设计实践作业提交模板

---

## 📋 学生信息

| 项目 | 内容 |
|------|------|
| **学号** | 202513080172 |
| **姓名** | [请填写您的姓名] |
| **班级** | [请填写您的班级] |
| **作业编号** | [请填写作业编号] |
| **提交日期** | [请填写提交日期] |

---

## 📁 目录结构
作业仓库/
├── README.md # 作业说明文档（本文件）
├── src/ # 源代码目录（必须）
│ ├── *.c # C 语言源文件
│ ├── *.cpp # C++ 语言源文件
│ ├── *.h # C 头文件
│ └── *.hpp # C++ 头文件
├── data/ # 测试数据目录（必须）
│ ├── input.txt # 输入测试数据
│ └── output.txt # 期望输出数据
├── tests/ # 单元测试目录（可选）
└── docs/ # 实验报告目录（可选）
└── report.md # 实验报告

text

---

## 📝 提交要求

### ✅ 必须提交
| 类型 | 要求 | 示例 |
|------|------|------|
| 源代码 | 所有 `.c`、`.cpp`、`.h` 文件放在 `src/` 目录 | `src/main.c` |
| 测试数据 | 所有 `.txt` 文本数据文件放在 `data/` 目录 | `data/input.txt` |
| 文档 | 填写完整的本 README.md 文件 | - |

### ❌ 禁止提交
- 编译产物：`*.exe`, `*.o`, `*.obj`, `*.out`
- 二进制文件：图片、音频、视频
- 压缩包：`*.zip`, `*.tar`, `*.gz`
- IDE 配置：`.vscode/`, `.idea/`, `*.swp`
- 临时文件：`*.tmp`, `*.log`, `*.bak`

---

## 🚀 快速开始

### 1. 克隆仓库到本地
```bash
git clone git@172.16.37.119:repositories/stu_学号.git 作业目录
cd 作业目录
2. 添加您的代码
bash
# 将您的源文件复制到 src 目录
cp ~/my_program.c src/

# 将测试数据复制到 data 目录
cp ~/test_data.txt data/
3. 编译程序
C 语言编译：

bash
gcc -Wall -g src/*.c -o program
# 或指定源文件
gcc -Wall -g src/main.c src/utils.c -o program
C++ 语言编译：

bash
g++ -Wall -g src/*.cpp -o program
# 或指定源文件
g++ -Wall -g src/main.cpp src/function.cpp -o program
4. 运行程序
bash
# 直接运行
./program

# 使用测试数据文件作为输入
./program < data/input.txt

# 将输出保存到文件
./program > data/my_output.txt
5. 提交作业
bash
# 查看修改状态
git status

# 添加所有文件
git add .

# 提交到本地仓库
git commit -m "提交作业：完成第X次作业"

# 推送到远程服务器
git push origin master
💡 代码示例
C 语言示例
c
// src/example.c
#include <stdio.h>
#include <stdlib.h>

/**
 * 计算两个整数的和
 * @param a 第一个整数
 * @param b 第二个整数
 * @return 两数之和
 */
int add(int a, int b) {
    return a + b;
}

int main() {
    int x = 10, y = 20;
    printf("%d + %d = %d\n", x, y, add(x, y));
    return 0;
}
C++ 语言示例
cpp
// src/example.cpp
#include <iostream>
#include <string>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    int subtract(int a, int b) {
        return a - b;
    }
};

int main() {
    Calculator calc;
    int a = 10, b = 5;
    
    cout << a << " + " << b << " = " << calc.add(a, b) << endl;
    cout << a << " - " << b << " = " << calc.subtract(a, b) << endl;
    
    return 0;
}
头文件示例
c
// src/example.h
#ifndef EXAMPLE_H
#define EXAMPLE_H

// 函数声明
int add(int a, int b);
int subtract(int a, int b);

// 常量定义
#define PI 3.14159
#define MAX_SIZE 100

#endif // EXAMPLE_H
测试数据示例
text
# data/input.txt
# 第一行：测试用例数量
3
# 测试数据：每行两个整数
10 20
30 40
50 60
📊 评分标准
评分项	权重	要求
代码正确性	40%	程序能正确运行，输出符合预期
代码规范性	20%	命名规范、注释清晰、缩进整齐
测试数据完整性	20%	提供充分的测试用例，覆盖边界情况
文档完整性	20%	README 填写完整，实验报告详实
🔧 常用 Git 命令
命令	说明
git status	查看当前文件状态
git add <文件>	添加指定文件到暂存区
git add .	添加所有修改的文件
git commit -m "说明"	提交到本地仓库
git push	推送到远程服务器
git pull	拉取远程最新版本
git log --oneline	查看提交历史
git diff	查看文件修改差异
❓ 常见问题
Q1: 推送时提示 "rejected"
bash
# 先拉取最新代码再推送
git pull origin master
git push origin master
Q2: 提交错了如何修改？
bash
# 修改最后一次提交
git add .
git commit --amend -m "新的提交信息"
git push --force origin master
Q3: 如何撤销未提交的修改？
bash
# 撤销所有未提交的修改
git checkout .

# 撤销指定文件
git checkout -- src/main.c
Q4: 如何查看某个文件的提交历史？
bash
git log --oneline src/main.c
Q5: 忘记添加 .gitignore 怎么办？
bash
# 创建 .gitignore 后，清除已跟踪的错误文件
git rm -r --cached *.exe
git rm -r --cached *.o
git add .gitignore
git commit -m "Add .gitignore"
📞 联系方式
如有问题，请联系：

老师邮箱：zgs@nuist.edu.cn

答疑时间：每周三 14:00-16:00

📝 作业提交检查清单
在提交前，请确认以下事项：

README.md 中的学生信息已填写完整

所有源代码已放入 src/ 目录

所有测试数据已放入 data/ 目录

程序能正常编译通过

程序运行结果正确

没有提交编译产物（.exe、.o 等）

没有提交临时文件（.tmp、.log 等）

已执行 git add . 添加所有文件

已执行 git commit 提交到本地

已执行 git push 推送到服务器

祝您作业顺利！ 🎉
