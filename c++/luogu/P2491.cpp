#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=300005;
int n, s;
int head[MX], cnt;
//  dis  --->以直径端点A为根时的距离
//  fa   --->父亲，用来回溯直径
int dis[MX], fa[MX];
//  belong  --->每个点挂在直径上的哪个点
//  off     --->到挂载点的距离
int belong[MX], off[MX];
//  pos   --->直径点在直径上的排名
//  pth   --->直径上的点，从A到B
//  ind   --->是否在直径上
int pos[MX], pth[MX], ind[MX], m;
//  bmax  --->最长的挂枝，与核的位置无关
int far, farD, bmax, D;
//  su/sf/sd  --->手写栈，栈里的点、来的位置、到根的dis
int su[MX], sf[MX], sd[MX];
struct node{
	int to, nex, w;
}edges[2*MX];

void add(int u, int v, int w) {
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}

//  以rt为根，算fa和dis，顺便拿到最远点
void dfs(int rt) {
	int top=0;
	fa[rt]=0;
	dis[rt]=0;
	su[++top]=rt;
	while(top) {
		int u=su[top--];
		for(int e=head[u]; e; e=edges[e].nex) {
			int v=edges[e].to;
			if(v==fa[u])  continue;
			fa[v]=u;
			dis[v]=dis[u]+edges[e].w;
			if(dis[v]>farD) {
				farD=dis[v];
				far=v;
			}
			su[++top]=v;
		}
	}
}

//  把直径点rt下面挂着的非直径子树染色，belong记rt，off记到rt的距离
void mark(int rt) {
	int top=0;
	for(int e=head[rt]; e; e=edges[e].nex) {
		int v=edges[e].to;
		if(ind[v])  continue;
		su[++top]=v;   sf[top]=rt;   sd[top]=edges[e].w;
	}
	while(top) {
		int u=su[top], f=sf[top], d=sd[top];
		top--;
		belong[u]=rt;
		off[u]=d;
		for(int e=head[u]; e; e=edges[e].nex) {
			int v=edges[e].to;
			if(v==f||ind[v])  continue;
			su[++top]=v;   sf[top]=u;   sd[top]=d+edges[e].w;
		}
	}
}

signed main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> s;
	for(int i=1; i<=n-1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u,v,w);
		add(v,u,w);
	}
	//  两遍dfs定出一条直径A-B
	farD=-1;
	dfs(1);
	int A=far;
	farD=-1;
	dfs(A);
	int B=far;
	D=dis[B];

	//  顺着父亲从B回溯到A，再反转成A到B
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

	//  直径点及其挂着子树打标记
	for(int k=1; k<=m; k++) {
		int u=pth[k];
		belong[u]=u;   off[u]=0;
		mark(u);
	}

	//  ecc=裸端点A,B在核外的余量 与 最长挂枝 取max，挂枝项与核无关
	bmax=0;
	for(int v=1; v<=n; v++)  bmax=max(bmax,off[v]);

	//  双指针：i右移时最优j也只会右移，j取到长度不超s的最远点
	int ans=1000000000000000000LL, j=1;
	for(int i=1; i<=m; i++) {
		if(j<i)  j=i;
		while(j+1<=m&&dis[pth[j+1]]-dis[pth[i]]<=s)  j++;
		int L=dis[pth[i]], R=D-dis[pth[j]];
		ans=min(ans,max(max(L,R),bmax));
	}
	cout << ans;
	return 0;
}
