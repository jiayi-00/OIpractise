# OIpractise

OI（信息学奥林匹克）算法练习代码库：洛谷 / CSP / Codeforces / USACO / 蓝桥杯等题目练习与算法模板。

## 目录结构

```text
c++/
├── 模板/                # 算法模板（树状数组、并查集、字典树、单调栈/队列、拓扑排序、
│                        #   差分约束、exgcd、乘法逆元、扩展欧拉定理、最小生成树、有理数取余等）
├── 题解/                # 各类题目题解：P 开头为洛谷题号，其余为比赛题 / 专题练习（文件名即题目）
├── CSP/                 # CSP-J/S 历年真题练习（含 2019 学生比赛、选手目录等）
├── codeforces/          # Codeforces 题目
├── USACO TRAINING/      # USACO Training 练习
├── 蓝桥杯练习/           # 蓝桥杯真题练习
└── 其他/                # 8 数码、函数递归、STL、化学难题等零散练习
```

## 使用

```bash
g++ -std=c++17 -O2 -o solution "题解/P1099.cpp"
./solution < input.txt
```

- 通用起手模板：[`c++/模板/template.cpp`](c++/模板/template.cpp)（含快读快写）
- 本地测试数据（`.in` / `.ans`）、编译产物（`.exe` / `.out`）、编辑器缓存（`.cph` / `.vscode`）不入库，见 `.gitignore`

## 约定

- 新题解按题库放入对应目录，文件名用「题号 + 题目简称」；
- 暴力 / 对拍 / 生成器等辅助代码放同目录 `_tools/` 下，或仅在本地保留；
- 提交信息示例：`feat(CSP): P7074 方格取数`
