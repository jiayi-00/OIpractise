#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=10007;
int n, m, t, K, ans;
int p[55], a[105][105], dp[55][55][105];
signed main(){
	cin >> n >> m >> t >> K;
	for (int i=1; i<=m; i++) {
		cin >> p[i];
	}
	for (int i=1; i<=t; i++) { 
		int x, y;
		cin >> x >> y;
		a[x][y]=1;
		a[y][x]=1;
	}
	for (int i=1; i<=m; i++) {
		
		dp[1][i][p[i]]=1;
	}
	for (int i=2; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			for(int s=p[j]; s<=K; s++){
				for (int k=1; k<=m; k++){
					if(a[j][k]==0){
						dp[i][j][s]=(dp[i][j][s]+dp[i-1][k][s-p[j]])%mod;
					}
				}
			}
		}
		for (int j=1; j<=m; j++){
			ans=(ans+dp[n][j][K])%mod;
		}
	}
	cout << ans;
	return 0;
} 
