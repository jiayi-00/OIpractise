#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e6+5;
int head[maxn],cnt;
int siz[maxn],a[maxn],dp[maxn],total[maxn];
int n;
struct node{
	int to,nex,w;
}edges[maxn];
void add(int u, int v, int w){
	edges[++cnt].nex=head[u];
	edges[cnt].to=v;
	edges[cnt].w=w;
	head[u]=cnt;
}
void dfs1(int i, int fa){
	siz[i]=a[i];
	dp[i]=0;
	for(int e=head[i]; e; e=edges[e].nex){
		int v=edges[e].to;
		if(v!=fa){
			dfs1(v, i);
			siz[i]+=siz[v];
			dp[i]+=dp[v]+siz[v]*edges[e].w;
		}
	}
}
void dfs2(int i, int fa, int tot){
	if(i!=1){
		int w_fa_u=0;
		for(int e=head[fa]; e; e=edges[e].nex){
			if(edges[e].to==i) {
				w_fa_u=edges[e].w;
				break;
			}
		}
		total[i]=total[fa]+(tot-2*siz[i])*w_fa_u;
	}
	else  total[i]=dp[i];
	for(int e=head[i]; e; e=edges[e].nex){
		int v=edges[e].to;
		if(v!=fa)  dfs2(v, i, tot);
	}
}
signed main(){
	cin>>n;
	for(int i=1; i<=n; i++)  cin>>a[i];
	for(int i=1; i<=n-1; i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs1(1,0);
	dfs2(1,0,siz[1]);
	int ans=total[1];
	for(int i=2; i<=n; i++)  ans=min(ans,total[i]);
	cout<<ans<<'\n';
	return 0;
} 
