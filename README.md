# LeetCode 8 Weeks

一个用于 8 周 LeetCode 训练的 C++ 仓库。

仓库目标是按主题推进刷题：每周聚焦一个核心模式，每天完成 2-3 道由易到难的题，并沉淀计划、题解和复盘记录。当前从“数组与哈希”开始。

## 目录结构

- `src/`: LeetCode 题解文件，通常每题一个 `.cpp`。
- `template/`: 本地调试模板和示例。
- `leetcode-plans/`: 分周训练计划。
- `.agents/skills/leetcode-weekly-coach/`: 项目共享 skill，用于生成周计划、每日题单和题解点评，是技能内容的唯一来源。
- `.codex/skills/`、`.claude/skills/`: 通过相对符号链接引用共享 skill 的代理兼容入口。
- `AGENTS.md`: 给 Codex 或其他协作代理看的项目规则。
- `header.h`: 常用数据结构、打印函数、计时器和本地测试辅助工具。

本地生成物和编辑器缓存会被 `.gitignore` 排除，例如 `.vscode/`、`src/.lcpr_data/`、`*.exe`。

## 训练方式

1. 先查看 `leetcode-plans/` 中当前周计划。
2. 在 `src/` 中完成对应题目的 LeetCode 代码。
3. 如需本地验证，使用 `template/` 或临时测试文件。
4. 题解完成后，可以补充复盘，重点记录模式识别、复杂度和易错边界。

当前计划：

- 第 01 周：数组与哈希
- 当前题目：`217. Contains Duplicate`

## 本地编译示例

```powershell
g++ -std=c++20 -DLOCAL template/template.cpp -o template/template.exe
```

生成的 `.exe` 文件不需要提交。

## 共享 Skill

本项目包含一个只服务于当前仓库的 skill：

- `$leetcode-weekly-coach`: 按主题制定 LeetCode 周计划、延续每日题单，并在提交题解后生成中文 Markdown 点评。

相关文件位于 `.agents/skills/leetcode-weekly-coach/`。如果修改训练路线或输出模板，优先更新该目录下的 `references/` 文件。`.codex/skills/` 和 `.claude/skills/` 中的同名入口均通过相对符号链接引用该目录，无需维护多份内容。

## Git 建议

提交前建议检查：

```powershell
git status --short
```

如果只是完成一道题，提交信息可以使用类似格式：

```text
Solve 217 Contains Duplicate
```
