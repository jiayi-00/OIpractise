#include <bits/stdc++.h>
using namespace std;
string x, y;
int dp[1005], p[1005];
int main() {
    
    cin >> x >> y;
    int n=x.size(), m=y.size();
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(x[i-1]==y[j-1]) {
                dp[j]=p[j-1] + 1;
            } else {
                dp[j]=max(p[j], dp[j-1]);
            }
        }
        swap(dp, p);
    }
    
    cout << p[m];
    return 0;
}