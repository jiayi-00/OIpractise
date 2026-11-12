#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, cnt;
int ans[10005], du[1005];
int a[1005][1005];
void dfs(int i){
	for(int j=1; j<=n; j++) {
		if(a[i][j]) {
			a[i][j]--;
			a[j][i]--;
			dfs(j);
		} 
	}
	ans[++cnt]=i;
}
signed main() {
	cin >> n >> m;
	for(int i=1; i<=m; i++) {
		int u, v;
		cin >> u >> v;
		du[u]++; du[v]++;
		a[u][v]++; a[v][u]++;
	}
	int total=0;
	for(int i=1; i<=n; i++) {
		if(du[i]%2==1)  total++;
	}
	if(total!=0 && total!=2) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	int q=1;
	for(int i=1; i<=n; i++) {
		if(du[i]%2==1) {
			q=i;
			break;
		}
	}
	dfs(q);
	for(int i=cnt; i>=1; i--) {
		cout << ans[i] << ' ';
	}
	return 0; 
}
 
