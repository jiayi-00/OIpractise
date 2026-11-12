#include<bits/stdc++.h>
using namespace std;

int n, a[35], f[35][35], pre[35];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }

    memset(f, 0x3f, sizeof(f)); // 用较大值初始化

    for (int i = 1; i <= n; i++)
        f[i][i] = 0;  // 一个丸子不需要力气

    for (int len = 2; len <= n; len++) {          // 区间长度
        for (int i = 1; i + len - 1 <= n; i++) { // 区间起点
            int j = i + len - 1;                 // 区间终点
            for (int k = i; k < j; k++) {        // 分割点
                f[i][j] = min(f[i][j],
                              f[i][k] + f[k+1][j] + pre[j] - pre[i-1]);
            }
        }
    }

    cout << f[1][n] << endl;
    return 0;
}
