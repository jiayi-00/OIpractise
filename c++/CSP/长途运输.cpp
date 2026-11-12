#include<iostream>
using namespace std;

int n,l[1001][1001],a,b,long_t,vis[1001];

void dfs(int i,int t){
	if(t>long_t){
		long_t=t;
	}
	for(int j=1; j<=n; j++){
		if(l[i][j]==1&&vis[j]==0){
			vis[j]=1;
			dfs(j,t+1);
			vis[j]=0;
		}
	}
}

int main(){
	
	cin>>n;
	for(int i=1; i<=n-1; i++){
		cin>>a>>b;
		l[a][b]=l[b][a]=1;
	} 
	vis[1]=1;
	dfs(1,0);
	cout<<long_t;
	
	return 0;
}
