#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, ans;
int dp[1000005], siz[1000005];
int cnt, head[1000005];
struct node{
	int to, nex;
}edges[2000005];
void add(int u,int v){
	edges[++cnt].to=v;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}
void dfs1(int i,int fa,int depth){
	dp[1]+=depth;
	siz[i]=1;
	for(int e=head[i]; e; e=edges[e].nex){
		int v=edges[e].to;
		if(v==fa)  continue;
		dfs1(v,i,depth+1);
		siz[i]+=siz[v];
	}
}
void dfs2(int i,int fa){
	for(int e=head[i]; e; e=edges[e].nex){
		int v=edges[e].to;
		if(v==fa)  continue;
		dp[v]=dp[i]-siz[v]+n-siz[v];
		dfs2(v,i);
	}
}
signed main(){
	cin >> n;
	for(int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0,0);
	dfs2(1,0);
	int mx=0;
	for(int i=1; i<=n; i++){
		mx=max(mx,dp[i]);
	}
	for(int i=1; i<=n; i++){
		if(dp[i]==mx) {
			ans=i;
			break;
		}
	}
	cout << ans;
	return 0;
} 
