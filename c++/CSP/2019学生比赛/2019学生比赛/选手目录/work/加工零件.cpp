#include<iostream>
#include<cstdio>
using namespace std;

int n,m,q,g[1001][1001],u,v,a,l;
bool f=0,h=0;

void go(int w,int p){
	if(h) return;
	if(w==1){
		if(g[p][1]==1) h=1;
		return;
	}
	for(int i=1; i<=n; i++){
		if(g[p][i]==1){
			go(w-1,i);
		}
	}
}

int main(){
	
	freopen("work.in","r",stdin);
	freopen("work.out","w",stdout);
	
	cin>>n>>m>>q;
	for(int i=1; i<=m; i++){
		cin>>u>>v;
		g[u][v]=g[v][u]=1;
	}
	for(int i=1; i<=q; i++){
		cin>>a>>l;
		if(l==1){
			if(g[a][1]==1) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}else {
			h=0;
			go(l,a);
			if(h==1) cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	
	
	return 0;
}
