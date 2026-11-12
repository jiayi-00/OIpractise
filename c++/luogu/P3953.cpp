// P3953 [NOIP2017 提高组] 逛公园 —— 本题只处理 k=0：求 1 -> n 的最短路条数 mod P，无穷多则输出 -1
// 做法: 正向 SPFA 求 dis[i] (1 到 i 最短路), 反图上从 n 跑 SPFA 求 rdis[i] (i 到 n 最短路)
//       i 在某条 1->n 最短路上 <=> dis[i]+rdis[i]==dis[n]
//       在最短路径 DAG (只留 dis[u]+w==dis[v] 的边) 上按拓扑序统计条数
//       拓扑排序结束后还有点有剩余入度 ---> DAG 上有环 ---> 环上边权全 0 ---> 无穷多 ---> -1
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1e5+5;
const int MXM=2e5+5;
const int INF=1e18;
int n, m, k, P, cnt, rcnt;
int head[MX], rhead[MX];
int dis[MX], rdis[MX], inq[MX], deg[MX], ad[MX], ok[MX];
queue<int> q;
struct node{
	int to, nex, w;
}edges[MXM], redges[MXM];
void add(int u, int v, int w){
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}
void radd(int u, int v, int w){
	redges[++rcnt].to=v;
	redges[rcnt].w=w;
	redges[rcnt].nex=rhead[u];
	rhead[u]=rcnt;
}
// 多测清空: 要先把本组的 n 读进来, 所以 init 在读入之后调用
void init(){
	memset(head, 0, sizeof(head));
	memset(rhead, 0, sizeof(rhead));
	memset(inq, 0, sizeof(inq));
	memset(deg, 0, sizeof(deg));
	memset(ad, 0, sizeof(ad));
	memset(ok, 0, sizeof(ok));
	for(int i=1; i<=n; i++)  dis[i]=rdis[i]=INF;
	q=queue<int> ();
	cnt=rcnt=0;
}
void spfa(){
	q.push(1);
	inq[1]=1;
	dis[1]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int e=head[u]; e; e=edges[e].nex){
			int v=edges[e].to;
			if(dis[u]+edges[e].w<dis[v]){
				dis[v]=dis[u]+edges[e].w;
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
}
void rspfa(){
	q.push(n);
	inq[n]=1;
	rdis[n]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int e=rhead[u]; e; e=redges[e].nex){
			int v=redges[e].to;
			if(rdis[u]+redges[e].w<rdis[v]){
				rdis[v]=rdis[u]+redges[e].w;
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
}
void solve(){
	cin >> n >> m >> k >> P;
	init();
	for(int i=1; i<=m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c);
		radd(b, a, c);
	}
	spfa();
	if(dis[n]>=INF){
		cout << 0 << '\n';
		return;
	}
	rspfa();
	// ok[i] ---> i 落在某条 1->n 的最短路上
	for(int i=1; i<=n; i++)
		if(dis[i]+rdis[i]==dis[n])  ok[i]=1;
	//  最短路径 DAG 的入度
	for(int u=1; u<=n; u++){
		if(!ok[u])  continue;
		for(int e=head[u]; e; e=edges[e].nex){
			int v=edges[e].to;
			if(ok[v] && dis[u]+edges[e].w==dis[v])  deg[v]++;
		}
	}
	//  ad[v] ---> 1 到 v 的最短路条数
	ad[1]=1;
	for(int i=1; i<=n; i++)
		if(ok[i] && !deg[i])  q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int e=head[u]; e; e=edges[e].nex){
			int v=edges[e].to;
			if(!ok[v] || dis[u]+edges[e].w!=dis[v])  continue;
			ad[v]=(ad[v]+ad[u])%P;
			if(--deg[v]==0)  q.push(v);
		}
	}
	for(int i=1; i<=n; i++)
		if(ok[i] && deg[i]){
			cout << -1 << '\n';
			return;
		}
	cout << ad[n]%P << '\n';
}
signed main(){
	int T;
	cin >> T;
	while(T--)  solve();
	return 0;
}
