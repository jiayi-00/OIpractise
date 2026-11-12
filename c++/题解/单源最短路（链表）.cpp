#include<bits/stdc++.h>
using namespace std;
int n,m,s,head[1000001],cnt,inq[1000001],dui[1000001],dis[1000001];
struct node{
	int to,next,len;
}edges[5000001];
void add(int a,int b,int w){
	edges[++cnt].to=b;
	edges[cnt].len=w;
	edges[cnt].next=head[a];
	head[a]=cnt;
}
int main(){
	cin>>n>>m>>s;
	for(int i=1; i<=m; i++){
		int a,b,w;
		cin>>a>>b>>w;
		add(a,b,w);
	}
	for(int i=1; i<=n; i++)  dis[i]=1e9;
	int t=0,h=0;
	dui[++t]=s;
	dis[s]=0;
	inq[s]=1;
	while(h!=t){
		int u=dui[h+1];	
		inq[u]=0;
		h++;
		for(int e=head[u]; e; e=edges[e].next){
			int v=edges[e].to;
			if(dis[v]>dis[u]+edges[e].len){
				dis[v]=dis[u]+edges[e].len;
				if(!inq[v]){
					inq[v]=1;
					dui[++t]=v;
				}
			}
		}
	}
	for(int i=1; i<=n; i++) {
		if(dis[i]==1e9)  cout<<0x7fffffff<<' ';
		else  cout<<dis[i]<<' ';
	}
	return 0;
}
