#include<iostream>
using namespace std;
int n,t[105][105],u,v,w,m=0x7fffffff,ans=m,s,p[105];
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) t[i][j]=m;
	}
	for(int i=1; i<=n; i++){
		cin>>w>>u>>v;
		p[i]=w;
		t[i][v]=t[v][i]=1;
		t[i][u]=t[u][i]=1;
	}
	for(int k=1; k<=n; k++){
		for(int j=1; j<=n; j++){
			for(int i=1; i<=n; i++){
				if(t[k][j]!=m && t[i][k]!=m){
					if(t[i][j]>t[i][k]+t[k][j]) t[i][j]=t[i][k]+t[k][j];
				}
			}
		}
	}
	for(int i=1; i<=n; i++){
		int s=0;
		for(int j=1; j<=n; j++){
			if(i!=j && t[i][j]!=m) s+=t[i][j]*p[j];
		}
		ans=min(ans, s);
	}
	cout<<ans;
	return 0;
}
