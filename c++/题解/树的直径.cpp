#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, ans;
int dis[200005];
int cnt, head[200005];
struct node{
	int to, nex, w;
}edges[400005];
void add(int u,int v,int w){
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}
void dfs(int u,int fa){
	for(int e=head[u]; e; e=edges[e].nex) {
		int v=edges[e].to;
		int w=edges[e].w;
		if(v==fa)  continue;
		dis[v]=dis[u]+w;
		dfs(v,u);
	}
}
signed main(){
	cin >> n;
	for(int i=1; i<n; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1,0);
	int mx=0,b;
	for(int i=1; i<=n; i++){
		if(dis[i]>mx){
			mx=dis[i];
			b=i;
		}
		dis[i]=0;
	}
	dfs(b,0);
	for(int i=1; i<=n; i++){
		ans=max(ans,dis[i]);
	}
	cout << ans ;
	return 0;
} 
