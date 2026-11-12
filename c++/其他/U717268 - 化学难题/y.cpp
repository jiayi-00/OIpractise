#include <bits/stdc++.h>
using namespace std;

/*
 * ==================== 最佳限定 ====================
 *
 * 1. 元素范围：53 种常见元素（H ~ Ra），覆盖初中化学全部元素
 * 2. 化合价：每元素存所有常见化合价，DFS 搜索是否存在合法组合
 *    （同一元素的所有原子取相同化合价）
 * 3. 已知局限（测试数据需规避）：
 *    - 混合化合价化合物：Fe₃O₄, Pb₃O₄ 等 → 无法判定，会被误判 wrong
 *    - 过氧化物：H₂O₂, Na₂O₂ 等 → O 在过氧化物中为 -1，表中只存了 -2
 *    - 金属氢化物：NaH, CaH₂ 等 → H 在其中为 -1，表中只存了 +1
 *    （如需支持，给 O 加 -1、给 H 加 -1 即可，但会产生 NaO 等假阳性）
 * 4. 原子质量：Cl = 35.5 是唯一常见非整数，用 double 存储
 *    若要避免浮点：全部 ×2 用 int（Cl=71, H=2, O=32...），输出时 / 2
 * 5. 化学式格式限定：仅 () 分组，下标 _n（n 为正整数），最大长度 ≤ 100
 *    元素符号首字母大写、第二字母小写
 * ====================
 */

// ==================== 三张数据表 ====================

// 表1: 有效元素符号集合（判断"元素符号书写错误"）
// 注：与表2的 key 完全一致，表2 .count(sym) 即可判断，单独列出仅为可读性
set<string> validElements;

// 表2: 相对原子质量（op=0 求相对分子质量）
map<string, double> atomicMass;

// 表3: 常见化合价列表（判断"化合价之和不等于0"）
// 每个元素存所有常见化合价，checkValence 用 DFS 搜索合法组合
map<string, vector<int>> valences;

void initTables() {
    struct E { string sym; double m; vector<int> v; };
    vector<E> t = {
        // ---------- 非金属 ----------
        {"H",  1,    {1}},              // 氢
        {"He", 4,    {0}},              // 氦
        {"B",  10.8, {3}},              // 硼
        {"C",  12,   {-4, 2, 4}},      // 碳（-4=CH₄, +2=CO, +4=CO₂）
        {"N",  14,   {-3, 2, 3, 4, 5}},// 氮（-3=NH₃, +2=NO, +3=N₂O₃, +4=NO₂, +5=N₂O₅）
        {"O",  16,   {-2}},             // 氧
        {"F",  19,   {-1}},             // 氟
        {"Ne", 20,   {0}},              // 氖
        {"Si", 28,   {4}},              // 硅
        {"P",  31,   {-3, 3, 5}},      // 磷（-3=PH₃, +3=P₂O₃, +5=P₂O₅）
        {"S",  32,   {-2, 4, 6}},      // 硫（-2=H₂S, +4=SO₂, +6=SO₃）
        {"Cl", 35.5, {-1, 1, 5, 7}},   // 氯（-1=NaCl, +1=HClO, +5=HClO₃, +7=HClO₄）
        {"Ar", 40,   {0}},              // 氩
        {"Se", 79,   {-2, 4, 6}},
        {"Br", 80,   {-1, 1, 5, 7}},
        {"Kr", 84,   {0}},
        {"I",  127,  {-1, 1, 5, 7}},
        {"Xe", 131,  {0}},
        {"Rn", 222,  {0}},
        {"As", 75,   {-3, 3, 5}},
        {"Te", 128,  {-2, 4, 6}},
        // ---------- 碱金属 / 碱土金属 ----------
        {"Li", 7,    {1}},
        {"Be", 9,    {2}},
        {"Na", 23,   {1}},
        {"Mg", 24,   {2}},
        {"K",  39,   {1}},
        {"Ca", 40,   {2}},
        {"Rb", 86,   {1}},
        {"Sr", 88,   {2}},
        {"Cs", 133,  {1}},
        {"Ba", 137,  {2}},
        {"Ra", 226,  {2}},
        // ---------- 过渡金属 ----------
        {"Sc", 45,   {3}},
        {"Ti", 48,   {3, 4}},
        {"V",  51,   {3, 5}},
        {"Cr", 52,   {2, 3, 6}},
        {"Mn", 55,   {2, 4, 6, 7}},
        {"Fe", 56,   {2, 3}},
        {"Co", 59,   {2, 3}},
        {"Ni", 59,   {2}},
        {"Cu", 64,   {1, 2}},
        {"Zn", 65,   {2}},
        {"Ag", 108,  {1}},
        {"Cd", 112,  {2}},
        {"Sn", 119,  {2, 4}},
        {"Sb", 122,  {-3, 3, 5}},
        {"Au", 197,  {1, 3}},
        {"Hg", 201,  {1, 2}},
        {"Tl", 204,  {1, 3}},
        {"Pb", 207,  {2, 4}},
        {"Bi", 209,  {3}},
        // ---------- 其他 ----------
        {"Al", 27,   {3}},
        {"Ga", 70,   {3}},
        {"Ge", 73,   {2, 4}},
    };
    for (auto& e : t) {
        validElements.insert(e.sym);
        atomicMass[e.sym] = e.m;
        valences[e.sym] = e.v;
    }
}

// ==================== 化合价合法性检查 ====================
// DFS：为每种元素选一个化合价，检查是否存在 sum(化合价 × 原子数) == 0
// 复杂度：O(∏|valences_i|)，实际公式中变价元素很少，通常 ≤ 几十次
bool dfsValence(int idx, long long sum, vector<pair<string, long long>>& elems) {
    if (idx == (int)elems.size()) return sum == 0;
    long long cnt = elems[idx].second;
    for (int v : valences[elems[idx].first])
        if (dfsValence(idx + 1, sum + v * cnt, elems)) return true;
    return false;
}

// atomCount: 每种元素的原子总数
bool checkValence(map<string, long long>& atomCount) {
    vector<pair<string, long long>> elems(atomCount.begin(), atomCount.end());
    return dfsValence(0, 0, elems);
}

// ==================== 工具函数 ====================

// 检查元素符号是否合法
bool isValidElement(const string& sym) {
    return validElements.count(sym) > 0;
}

// 计算相对分子质量（op=0）
double getMolarMass(map<string, long long>& atomCount) {
    double m = 0;
    for (auto& [sym, cnt] : atomCount)
        m += atomicMass[sym] * cnt;
    return m;
}

// 判断单质/化合物（op=1）
// 只有 1 种元素 → 单质(s)；多种元素 → 化合物(c)
bool isSimpleSubstance(map<string, long long>& atomCount) {
    return atomCount.size() == 1;
}

// ==================== 示例 ====================
int main() {
    initTables();

    // 示例: CO₂  →  C:1, O:2
    map<string, long long> co2 = {{"C", 1}, {"O", 2}};

    // 示例: H₂SO₄ →  H:2, S:1, O:4
    map<string, long long> h2so4 = {{"H", 2}, {"S", 1}, {"O", 4}};

    // 示例: Fe₂O₃ →  Fe:2, O:3
    map<string, long long> fe2o3 = {{"Fe", 2}, {"O", 3}};

    // --- CO₂ ---
    printf("CO2: valid=%d  valence=%d  mass=%.1f  %s\n",
        isValidElement("C") && isValidElement("O"),
        checkValence(co2),
        getMolarMass(co2),
        isSimpleSubstance(co2) ? "s" : "c");
    // 输出: CO2: valid=1  valence=1  mass=44.0  c

    // --- H₂SO₄ ---
    printf("H2SO4: valid=%d  valence=%d  mass=%.1f  %s\n",
        isValidElement("H") && isValidElement("S") && isValidElement("O"),
        checkValence(h2so4),
        getMolarMass(h2so4),
        isSimpleSubstance(h2so4) ? "s" : "c");
    // 输出: H2SO4: valid=1  valence=1  mass=98.0  c
    // (S=+6: 2×1 + 6 + 4×(-2) = 0 ✓)

    // --- Fe₂O₃ ---
    printf("Fe2O3: valid=%d  valence=%d  mass=%.1f  %s\n",
        isValidElement("Fe") && isValidElement("O"),
        checkValence(fe2o3),
        getMolarMass(fe2o3),
        isSimpleSubstance(fe2o3) ? "s" : "c");
    // 输出: Fe2O3: valid=1  valence=1  mass=160.0  c
    // (Fe=+3: 2×3 + 3×(-2) = 0 ✓)

    // --- Fe₃O₄（已知局限：混合化合价，会误判） ---
    map<string, long long> fe3o4 = {{"Fe", 3}, {"O", 4}};
    printf("Fe3O4: valence=%d  (应为1但输出0，混合化合价无法处理)\n",
        checkValence(fe3o4));
    // 输出: Fe3O4: valence=0  ← 错误！测试数据需规避

    return 0;
}
