#include<bits/stdc++.h>
using namespace std;
struct node
{
	int to,next;
}edges[20005];
int head[10005],du[10005],st[10005],w[10005];
int n,m,cnt,top,ans;
void add(int a,int b)
{
	edges[++cnt].to=b;
	edges[cnt].next=head[a];
	head[a]=cnt;
	du[b]++;
}
int main(){
	cin>>n>>m;
	for(int i=1; i<=m; i++)
	{
		int a,b;
		cin>>a>>b;
		add(b,a);
	}
	for(int i=1; i<=n; i++)
	{
		if(du[i]==0) 
		{
			st[++top]=i;
			w[i]=100;
		} 
	}
	while(top)
	{
		int u=st[top--];
		for(int e=head[u]; e; e=edges[e].next)
		{
			int v=edges[e].to;
			du[v]--;
			if(du[v]==0)  st[++top]=v;
			w[v]=max(w[v],w[u]+1);
		}
	}
	bool f=1;
	for(int i=1; i<=n; i++)
	{
		ans+=w[i];
		if(du[i])  f=0;
	}
	if(f)  cout<<ans;
	else  cout<<"Oh no";
	return 0;
} 
