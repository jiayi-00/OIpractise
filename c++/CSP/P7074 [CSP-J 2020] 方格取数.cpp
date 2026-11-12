#include <iostream>
#include <climits>
using namespace std;

const int MAXN = 1005;
const long long INF = 1e18;

long long a[MAXN][MAXN];
long long dp[MAXN][MAXN];
long long from_left[MAXN];
long long down[MAXN];
long long up[MAXN];

int main() {
    int n, m;
    cin >> n >> m;
    
    // 读入数据
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    
    // 初始化 dp 为负无穷
    for (int i = 0; i <= n+1; i++) {
        for (int j = 0; j <= m+1; j++) {
            dp[i][j] = -INF;
        }
    }
    
    // 初始化第一列
    dp[1][1] = a[1][1];
    for (int i = 2; i <= n; i++) {
        dp[i][1] = dp[i-1][1] + a[i][1];
    }
    
    // 处理第 2 列到第 m 列
    for (int j = 2; j <= m; j++) {
        // 初始化数组
        for (int i = 1; i <= n; i++) {
            from_left[i] = -INF;
            down[i] = -INF;
            up[i] = -INF;
        }
        
        // 计算从左边进入的得分
        for (int i = 1; i <= n; i++) {
            if (dp[i][j-1] != -INF) {
                from_left[i] = dp[i][j-1] + a[i][j];
            }
        }
        
        // 向下走
        down[1] = from_left[1];
        for (int i = 2; i <= n; i++) {
            if (down[i-1] != -INF) {
                down[i] = (from_left[i] > down[i-1] + a[i][j]) ? from_left[i] : (down[i-1] + a[i][j]);
            } else {
                down[i] = from_left[i];
            }
        }
        
        // 向上走
        up[n] = from_left[n];
        for (int i = n-1; i >= 1; i--) {
            if (up[i+1] != -INF) {
                up[i] = (from_left[i] > up[i+1] + a[i][j]) ? from_left[i] : (up[i+1] + a[i][j]);
            } else {
                up[i] = from_left[i];
            }
        }
        
        // 合并两个方向
        for (int i = 1; i <= n; i++) {
            dp[i][j] = (down[i] > up[i]) ? down[i] : up[i];
        }
    }
    
    cout << dp[n][m] << endl;
    
    return 0;
}
