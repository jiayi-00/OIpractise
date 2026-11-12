#include<bits/stdc++.h>
using namespace std;
int n,m,head[1001],cnt,inq[1001],dui[1001],dis[1001];
struct node{
	int to,next;
}edges[5001];
void add(int a,int b){
	edges[++cnt].to=b;
	edges[cnt].next=head[a];
	head[a]=cnt;
}
int main(){
	cin>>n>>m;
	for(int i=1; i<=m; i++){
		int a,b;
		cin>>a>>b;
		add(a,b);
	}
	for(int i=1; i<=n; i++)  dis[i]=1e9;
	int t=0,h=0;
	dui[++t]=1;
	dis[1]=0;
	inq[1]=1;
	while(h!=t){
		int u=dui[h+1];	
		inq[u]=0;
		h++;
		for(int e=head[u]; e; e=edges[e].next){
			int v=edges[e].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!inq[v]){
					inq[v]=1;
					dui[++t]=v;
				}
			}
		}
	}
	for(int i=1; i<=n; i++) {
		if(dis[i]==1e9)  cout<<0<<' ';
		else  cout<<dis[i]<<' ';
	}
	return 0;
}
