#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, ans;
int cnt[25], a[25][25];
int dp[25][1024*1024+5];
signed main(){
	cin >> n >> m;
	for (int i=1; i<=n; i++) {
		cin >> cnt[i];
		for (int j=1; j<=cnt[i]; j++) {
			cin >> a[i][j];
		}
	}
	dp[0][0]=1;
	for (int i=1; i<=n; i++) {
		for (int j=0; j<(1<<m); j++) {
			for (int k=1; k<=cnt[i]; k++) {
				int pos=a[i][k]-1;
				if ((j&(1<<pos))!=0) {
					int l=(j^(1<<pos));
					dp[i][j]+=dp[i-1][l];
				}
			}
			if (i==n){
				ans+=dp[i][j];
			}
		}
	}
	cout << ans;
	return 0;
} 
