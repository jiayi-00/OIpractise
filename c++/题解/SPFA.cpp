#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt;
int head[2005],dist[2005],cnt_path[2005],inq[2005];
queue<int> q;
struct node{
	int to,w,next;
}edges[8000005];
void add(int u,int v,int w){
	edges[++cnt].to=v;
	edges[cnt].w=w;
	edges[cnt].next=head[u];
	head[u]=cnt;
}
signed main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++) dist[i]=0x7fffffff;
	for(int i=1; i<=m; i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	dist[1]=0;
	cnt_path[1]=1;
	q.push(1);
	inq[1]=1;
	while(!q.empty()){
		int a=q.front();
		q.pop();
		inq[a]=0;
		for(int e=head[a];e;e=edges[e].next){
			int u=edges[e].to;
			int w=edges[e].w;
			if(dist[a]+w<dist[u]){
				dist[u]=dist[a]+w;
				cnt_path[u]=cnt_path[a];
				if(!inq[u]){
					q.push(u);
					inq[u]=1;
				}
			}
			else if(dist[a]+w==dist[u]){
				cnt_path[u]=cnt_path[u]+cnt_path[a];
			}
		}
	}
	cout<<dist[n]<<' '<<cnt_path[n]%1000000007;
	return 0;
}
