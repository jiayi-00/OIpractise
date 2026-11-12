#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

/* ================= 快读 ================= */
namespace io {
const int SZ = 1 << 20;
char ibuf[SZ], *i1 = ibuf, *i2 = ibuf;
char gc() {
    if (i1 == i2) i1 = ibuf, i2 = ibuf + fread(ibuf, 1, SZ, stdin);
    return i1 == i2 ? EOF : *i1++;
}
template <class T> bool rd(T &x) {
    char c = gc();
    if (c == EOF) return false;
    bool neg = false;
    x = 0;
    while (c != '-' && (c < '0' || c > '9')) {
        c = gc();
        if (c == EOF) return false;
    }
    if (c == '-') neg = true, c = gc();
    while (c >= '0' && c <= '9') x = x * 10 + (c - '0'), c = gc();
    if (neg) x = -x;
    return true;
}
template <class T, class... R> bool rd(T &x, R &...r) { return rd(x) && rd(r...); }
} // namespace io
using io::rd;

/* ================ 主程序 ================ */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;  // 多组数据

    while (T--) {
        // TODO: 读入 -> 处理 -> 输出
    }

    return 0;
}
