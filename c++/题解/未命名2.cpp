#include<bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001],dp[1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1; i<=m; i++){
		int x,y;
		cin>>x>>y;
		a[x][y]=1;
	}
	dp[0][1]=1;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(!a[i][j])  dp[i][j]=(dp[i-1][j]+dp[i][j-1])%100003;
		}
	}
	cout<<dp[n][n]<<endl;
	return 0;
}
