#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=305;
int n, s;
int head[MX], cnt;
//  dis  --->distance from diameter endpoint A
//  fa   --->father, used to trace back the diameter
int dis[MX], fa[MX];
//  belong  --->which diameter node this node hangs on
//  off     --->distance to that hanging point
int belong[MX], off[MX];
//  pos   --->rank of a diameter node on the diameter
//  pth   --->nodes on the diameter, from A to B
//  ind   --->whether the node lies on the diameter
int pos[MX], pth[MX], ind[MX], m;
int far, farD;
struct node{
	int to, nex, w;
}edges[2*MX];

void add(int u, int v, int w) {
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}

void dfs(int u, int f, int d) {
	fa[u]=f;
	dis[u]=d;
	if(d>farD) {
		farD=d;
		far=u;
	}
	for(int e=head[u]; e; e=edges[e].nex) {
		int v=edges[e].to;
		if(v==f)  continue;
		dfs(v,u,d+edges[e].w);
	}
}

//  color the non-diameter subtree hanging on a diameter node
void mark(int u, int f, int d, int rt) {
	belong[u]=rt;
	off[u]=d;
	for(int e=head[u]; e; e=edges[e].nex) {
		int v=edges[e].to;
		if(v==f||ind[v])  continue;
		mark(v,u,d+edges[e].w,rt);
	}
}

signed main(){
	cin >> n >> s;
	for(int i=1; i<=n-1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u,v,w);
		add(v,u,w);
	}
	//  two dfs to fix one diameter A-B
	farD=-1;
	dfs(1,0,0);
	int A=far;
	farD=-1;
	dfs(A,0,0);
	int B=far;

	//  trace back from B to A, then reverse into A to B
	m=0;
	for(int u=B; ; u=fa[u]) {
		pth[++m]=u;
		if(u==A)  break;
	}
	for(int k=1; k<=m/2; k++)  swap(pth[k],pth[m-k+1]);
	for(int k=1; k<=m; k++) {
		ind[pth[k]]=1;
		pos[pth[k]]=k;
	}

	//  mark every diameter node and its hanging subtrees
	for(int k=1; k<=m; k++) {
		int u=pth[k];
		belong[u]=u;   off[u]=0;
		for(int e=head[u]; e; e=edges[e].nex) {
			int v=edges[e].to;
			if(ind[v])  continue;
			mark(v,u,edges[e].w,u);
		}
	}

	//  enumerate the core interval, ecc=max(left rest, right rest, longest hanging branch)
	int ans=1000000000;
	for(int i=1; i<=m; i++) {
		for(int j=i; j<=m; j++) {
			if(dis[pth[j]]-dis[pth[i]]>s)  break;
			int ecc=0;
			for(int v=1; v<=n; v++) {
				int p=pos[belong[v]];
				int d;
				if(p<i)  d=off[v]+dis[pth[i]]-dis[pth[p]];
				else if(p>j)  d=off[v]+dis[pth[p]]-dis[pth[j]];
				else  d=off[v];
				ecc=max(ecc,d);
			}
			ans=min(ans,ecc);
		}
	}
	cout << ans;
	return 0;
}
