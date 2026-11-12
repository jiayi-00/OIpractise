#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=100005;
int n, m, s;
int head[MX], cnt;
int dis[MX], ok[MX];

struct edge{
	int to, nex, w;
} edges[500005];
struct node{
	int dis, id;
	bool operator < (const node &x) const {
		return x.dis<dis;
	}
};
void add(int u,int v,int w){
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}
priority_queue <node > q;
void dijkstra(){
	for(int i=1; i<=n; i++)  dis[i]=0x7fffffff;
	dis[s]=0;
	q.push((node){0,s});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(ok[u])  continue;
		ok[u]=1;
		for(int e=head[u]; e; e=edges[e].nex){
			int v=edges[e].to;
			if(!ok[v] && dis[v]>dis[u]+edges[e].w){
				dis[v]=dis[u]+edges[e].w;
				q.push((node){dis[v], v});
			}
		}
	}
}
signed main(){
	cin >> n >> m >> s;
	for(int i=1; i<=m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		add(u,v,w);
	}
	dijkstra();
	for(int i=1; i<=n; i++){
		cout << dis[i] << ' ';
	}
	
	return 0;
}
