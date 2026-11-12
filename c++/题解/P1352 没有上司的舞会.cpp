#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, s;
int dp[6005][2], r[6005], a[6005];
vector<int> son[6005];
void dfs(int i){
	dp[i][1]=r[i];
	for(int j=0; j<son[i].size(); j++){
		int t=son[i][j];
		dfs(t);
		dp[i][0]+=max(dp[t][0],dp[t][1]);
		dp[i][1]+=dp[t][0];
	}
}
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> r[i];
	}
	for(int i=1; i<n; i++) {
		int k, l;
		cin >> l >> k;
		son[k].push_back(l);
		a[l]=k;
	}
	for(int i=1; i<=n; i++) {
		if(a[i]==0) {
			s=i;
			break;
		}
	}
	dfs(s);
	int ans=max(dp[s][0],dp[s][1]);
	cout << ans;
	return 0;
} 
